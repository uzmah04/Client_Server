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
	int socketCli, len_cli, connect_serv, receive_serv, closing;

	struct sockaddr_in serv_addr;

	char buffer[1024];

	socketCli = socket(AF_INET, SOCK_STREAM, 0);
	if ( socketCli == -1 )
        {
                perror("Socket");
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
                perror("Connect");
                exit(-1);
        }
        else
        {
                printf("[+] Connection Successfully Established \n");
        }

	receive_serv = recv(socketCli, buffer, 1024, 0);
	if ( receive_serv == -1 )
        {
                perror("Receive");
                exit(-1);
        }
        else
        {
                printf("[+] Data Received \n");
        }

	printf("Data Received: %s \n", buffer);
	printf("Received %d bytes from server\n", receive_serv);

	closing = close(socketCli);
	if ( closing == -1 )
        {
                perror("Close");
                exit(-1);
        }
        else
        {
                printf("[+] Closing the connection... \n");
        	printf("[+] Connection Successfully Closed \n");
	}

	return 0;
}
