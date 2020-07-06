#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

int main()
{
	int socketserv, bindserv, listenserv, len, acceptserv, send_cli, receiv_cli, closing;
	struct sockaddr_in serv_addr, cli_addr;

	char msgCli[1024], msgServ[2048];

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

	bzero(msgServ, 2048);
	strcpy(msgServ, "Hello! How can I help you? Do you want to: \n 1)  Obtain a document \n 2)  Obtain the list of document on the server \n 3)  Delete a document on the server \n 4)  Close connection \n");
        send_cli = send(acceptserv, msgServ, 2048, 0);
	if ( send_cli == -1 )
        {
                perror("[-] Error In Forwarding Data");
                exit(-1);
        }
	printf("SERVER Response:\n%s \n", msgServ);

	int exit_loop = 1;
	while(exit_loop == 1)
	{
		bzero(msgCli, 1024);
		receiv_cli = recv(acceptserv, msgCli, 1024, 0);
		if ( receiv_cli == -1 )
        	{
        	        perror("[-] Error In Receiving Data");
        	        exit(-1);
        	}
		printf("CLIENT Response:\n%s \n", msgCli);

		if ( strcmp(msgCli, "4") == 0 )
		{
			exit_loop = 4;
		}
		else
		{
			int x = atoi(msgCli);
			switch(x)
			{
				case 1:
				{
					bzero(msgServ, 2048);
				        strcpy(msgServ, "1) Doc ");
				        send_cli = send(acceptserv, msgServ, 2048, 0);
        				if ( send_cli == -1 )
        				{
                				perror("[-] Error In Forwarding Data");
                				exit(-1);
        				}
        				printf("SERVER Response:\n%s \n", msgServ);
					break;
				}

				case 2:
				{
					bzero(msgServ, 2048);
                                        strcpy(msgServ, "2) Liste Doc ");
                                        send_cli = send(acceptserv, msgServ, 2048, 0);
                                        if ( send_cli == -1 )
                                        {
                                                perror("[-] Error In Forwarding Data");
                                                exit(-1);
                                        }
                                        printf("SERVER Response:\n%s \n", msgServ);
					break;
				}

				case 3:
				{
					bzero(msgServ, 2048);
                                        strcpy(msgServ, "3) Delete Doc ");
                                        send_cli = send(acceptserv, msgServ, 2048, 0);
                                        if ( send_cli == -1 )
                                        {
                                                perror("[-] Error In Forwarding Data");
                                                exit(-1);
                                        }
                                        printf("SERVER Response:\n%s \n", msgServ);
					break;
				}

				default:
				{
					bzero(msgServ, 2048);
					strcpy(msgServ, "Error\n");
					send_cli = send(acceptserv, msgServ, 2048, 0);
				        if ( send_cli == -1 )
				        {
				                perror("[-] Error In Forwarding Data");
                				exit(-1);
        				}
        				printf("SERVER Response:\n%s \n", msgServ);
					break;
				}
			}
		}
	}

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
