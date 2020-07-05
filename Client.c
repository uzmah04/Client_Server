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
	int socketCli, len_cli, connect_serv, receive_serv, send_serv, closing;

	struct sockaddr_in serv_addr;

	char messageCli[1024], messageServ[2048];

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
	serv_addr.sin_addr.s_addr = inet_addr("192.168.100.54");

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

	int exit_loop = 1;
	while(exit_loop == 1)
	{
		bzero(messageServ, 2048);
		receive_serv = recv(socketCli, messageServ, 2048, 0);
		if ( receive_serv == -1 )
        	{
                	perror("[-] Error In Receiving Data ");
                	exit(-1);
        	}
        	printf("\nServer:\n%s \n", messageServ);

		bzero(messageCli, 1024);
		printf("Client:\n ");
		scanf("%s", messageCli);
		send_serv = send(socketCli, messageCli, 1024, 0);
		if ( send_serv == -1 )
        	{
                	perror("[-] Error In Forwarding Data");
                	exit(-1);
        	}

		if ( strcmp(messageCli, "4") == 0 )
		{
			exit_loop = 4;
		}

	}

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
