#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>

// To check errors
int check_error(int check)
{
        if ( check == -1 )
        {
                perror("[-] Error In Forwarding/Receiving Data");
                exit(-1);
        }

}

// Transfer a file from server to client
void send_file(char *filename, int acceptserv)
{
	char doc[2048];

	FILE *fp;
	fp=fopen(filename, "r");

	if( fp == NULL )
	{
		printf("[-] Error In Opening File... \n");
		return;
	}

	while( fgets(doc, 2048, fp) != NULL )
	{
		int send_file = send(acceptserv, doc, sizeof(doc), 0);
		check_error(send_file);
	}
	bzero(doc, 2048);

	printf("\n[+] Receiving File... \n");
	printf("[+] File Successfully Sent \n");
	return;
}

int main()
{
	int socketserv, bindserv, listenserv, len, acceptserv, send_cli, receiv_cli, closing;
	struct sockaddr_in serv_addr, cli_addr;

	char msgCli[1024], msgServ[2048];

	// Creation of socket; add ip address, port number,...
	socketserv = socket(AF_INET, SOCK_STREAM, 0);
	if ( socketserv == -1 )
	{
		perror("[-] Server Socket Creation Unsucessful ");
		exit(-1);
	}
	else
	{
		printf("[+] Server Socket Successfully Created \n");
	}

        memset(&(serv_addr.sin_zero), '\0', 8);

	bzero((char *)&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family= AF_INET;
	serv_addr.sin_port = htons(44440);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// To associate a socket with the port on the local machine
	bindserv = bind(socketserv, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if ( bindserv == -1 )
        {
                perror("[-] Bind To Port Unsuccessful ");
                exit(-1);
        }
        else
        {
                printf("[+] Bind To Port Successful \n");
        }

	// Wait for incoming connections
	listenserv = listen(socketserv, 3);
	if ( listenserv == -1 )
        {
                perror("[-] Listening Unsuccessful ");
                exit(-1);
        }
        else
        {
                printf("[+] Listening... \n");
        }

	// Accept the connection of the client who is connecting with the server
	len = sizeof(cli_addr);
	acceptserv = accept(socketserv, (struct sockaddr *)&cli_addr, &len);
	if ( acceptserv == -1 )
        {
                perror("[-] Connection To Client Unsucessful ");
                exit(-1);
        }
        else
        {
                printf("[+] Connection To Client Successful \n");
        }

		// Chat between client and server using send() and recv()
	bzero(msgServ, 2048);
	strcpy(msgServ, "Hello! How can I help you? Do you want to: \n 1)  Obtain a document \n 2)  Obtain the list of document on the server \n 3)  Delete a document on the server \n 4)  Close connection \n");
        send_cli = send(acceptserv, msgServ, 2048, 0);
	check_error(send_cli);
	printf("\nSERVER Response:\n%s \n", msgServ);

	int exit_loop = 1;
	while(exit_loop == 1)
	{
		bzero(msgCli, 1024);
		receiv_cli = recv(acceptserv, msgCli, 1024, 0);
		check_error(receiv_cli);
		printf("CLIENT Response:\n%s \n", msgCli);

		// To exit loop to end connection
		if ( strcmp(msgCli, "4") == 0 )
		{
			exit_loop = 4;
		}
		else
		{
			int x = atoi(msgCli);
			switch(x)
			{
				// To obtain specific document on the server
				case 1:
				{
					bzero(msgServ, 2048);
				        strcpy(msgServ, " Which document do you want? \n");
					send_cli = send(acceptserv, msgServ, 2048, 0);
                                        check_error(send_cli);
                                        printf("\nSERVER Response:\n%s \n", msgServ);

					bzero(msgCli, 1024);
                			receiv_cli = recv(acceptserv, msgCli, 1024, 0);
                			check_error(receiv_cli);
		                	printf("CLIENT Response:\n%s \n", msgCli);

					send_file(msgCli, acceptserv);

					break;
				}

				// To obtain list of documents available on server
				case 2:
				{
					char list[2048];

        				DIR *d;
       					struct dirent *dir;
        				d = opendir("~/home/uzmah/Documents");

				        if (d)
        				{
                				while ((dir = readdir(d)) != NULL)
                				{
                        				printf("%s\n", dir->d_name);
                				}
                				closedir(d);
        				}

					bzero(msgServ, 2048);
                                        strcpy(msgServ, dir->d_name);
                                        send_cli = send(acceptserv, msgServ, 2048, 0);
					check_error(send_cli);
                                        printf("SERVER Response:\n%s \n", msgServ);
					break;
				}

				// To delete a document from server
				case 3:
				{
					bzero(msgServ, 2048);
                                        strcpy(msgServ, " Which document do you want to delete? \n");
                                        send_cli = send(acceptserv, msgServ, 2048, 0);
                                        check_error(send_cli);
                                        printf("\nSERVER Response:\n%s \n", msgServ);

                                        bzero(msgCli, 1024);
                                        receiv_cli = recv(acceptserv, msgCli, 1024, 0);
                                        check_error(receiv_cli);
                                        printf("CLIENT Response:\n%s \n", msgCli);

                                        remove(msgCli);

					printf("\n[+] Deleting File... \n");
					printf("\n[+] Success In Deleting Files \n");

					break;
				}

				default:
				{
					bzero(msgServ, 2048);
					strcpy(msgServ, " You May Continue Or Retry \n");
					send_cli = send(acceptserv, msgServ, 2048, 0);
					check_error(send_cli);
	     				printf("\nSERVER Response:\n%s \n", msgServ);
					break;
				}
			}
		}
	}

	// To close the connection between client and server
	closing = close(socketserv);
        if ( closing == -1 )
        {
	        perror("[-] Closing Connection Unsucessful ");
	        exit(-1);
	}
	else
        {
        	printf("[+] Disconnecting... \n");
                printf("[+] Connection Successfully Closed \n");
        }

	return 0;
}
