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

// Receive a file from server
void receive_file(char *filename, int  socketCli)
{
	char doc[2048];
	int n, file_content;

	FILE *fp;
	fp=fopen(filename, "w");

	if( fp == NULL )
        {
                printf("[-] Error In Creating File... \n");
        }

	file_content = recv(socketCli, doc, 2048, 0);
	fprintf(fp, "%s", doc);
	fclose(fp);
	bzero(doc, 2048);

	printf("\n[+] Receiving File... \n");
	printf("[+] File Successfully Received \n");
}

int main()
{
	int socketCli, len_cli, connect_serv, receive_serv, send_serv, closing;

	struct sockaddr_in serv_addr;

	char messageCli[1024], messageServ[2048];

	// Creation of socket; add ip address, port number,...
	socketCli = socket(AF_INET, SOCK_STREAM, 0);
	if ( socketCli == -1 )
        {
                perror("[-1] Server Socket Creation Unsuccessful ");
                exit(-1);
        }
        else
        {
                printf("[+] Client Socket Successfully Created \n");
        }

	memset(&(serv_addr.sin_zero), '\0', 8);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(44440);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// To connect with the server
	len_cli = sizeof(serv_addr);
	connect_serv = connect(socketCli, (struct sockaddr *)&serv_addr, len_cli);
	if ( connect_serv == -1 )
        {
                perror("[-] Error In Establishing Connection ");
                exit(-1);
        }
        else
        {
                printf("[+] Connection Successfully Established \n");
        }

		// Chat between client and server using send() and recv()
	int exit_loop = 1;
	while(exit_loop == 1)
	{
		bzero(messageServ, 2048);
		receive_serv = recv(socketCli, messageServ, 2048, 0);
		check_error(receive_serv);
        	printf("\nSERVER:\n%s \n", messageServ);

		bzero(messageCli, 1024);
		printf("CLIENT:      ");
		scanf("%s", messageCli);
		send_serv = send(socketCli, messageCli, 1024, 0);
		check_error(send_serv);

		// To exit loop to end connection
		if ( strcmp(messageCli, "4") == 0 )
		{
			exit_loop = 4;
		}
		else
		{
			int x = atoi(messageCli);
			switch(x)
			{
				// To obtain specific document on the server
				case 1:
				{
					bzero(messageServ, 2048);
	                		receive_serv = recv(socketCli, messageServ, 2048, 0);
        	        		check_error(receive_serv);
			           	printf("\nSERVER:\n%s \n", messageServ);

                			bzero(messageCli, 1024);
                			printf("CLIENT:     ");
                			scanf("%s", messageCli);
                			send_serv = send(socketCli, messageCli, 1024, 0);
					check_error(send_serv);

					receive_file(messageCli, socketCli);

					strcpy(messageCli, "Client Received File Successfully \n");
					send_serv = send(socketCli, messageCli, 1024, 0);
                                        check_error(send_serv);

					break;
				}

                                // To obtain list of documents available on server
				case 2:
				{
					bzero(messageServ, 2048);
                                        receive_serv = recv(socketCli, messageServ, 2048, 0);
                                        check_error(receive_serv);
                                        printf("\nSERVER:\n%s \n", messageServ);
					break;
				}

				// To delete a document from server
				case 3:
				{
					bzero(messageServ, 2048);
                                        receive_serv = recv(socketCli, messageServ, 2048, 0);
                                        check_error(receive_serv);
                                        printf("\nSERVER:\n%s \n", messageServ);

                                        bzero(messageCli, 1024);
                                        printf("CLIENT:     ");
                                        scanf("%s", messageCli);
                                        send_serv = send(socketCli, messageCli, 1024, 0);
                                        check_error(send_serv);

					strcpy(messageCli, "Client Request Successfully Completed \n");
                                        send_serv = send(socketCli, messageCli, 1024, 0);
                                        check_error(send_serv);

					printf("\n%s \n",messageCli);

                                        break;
				}

				default:
				{
					bzero(messageCli, 1024);
                                        strcpy(messageCli, " Wrong Selection \n");
					printf("\n%s \n", messageCli);
                                        send_serv = send(socketCli, messageCli, 1024, 0);
                                        check_error(send_serv);
                                        break;

				}
			}
		}
	}


	// To close the connection between client and server
	closing = close(socketCli);
	if ( closing == -1 )
	{
        	perror("[-] Closing Connection Unsuccessful ");
                exit(-1);
        }
       	else
       	{
                printf("[+] Disconnecting... \n");
                printf("[+] Connection Successfully Closed \n");
	}

	return 0;
}
