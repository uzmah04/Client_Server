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
	int socketserv, bindserv, listenserv, len, acceptserv, send_cli, closing;
	struct sockaddr_in serv_addr, cli_addr;

	char buffer[1024];

	socketserv = socket(AF_INET, SOCK_STREAM, 0);
	if ( socketserv == -1 )
	{
		perror("Socket");
		exit(-1);
	}
	else
	{
		printf("[+] Server Socket Successfully Created \n");
	}

        memset(&(serv_addr.sin_zero), '\0', 8);

	bzero((char *)&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(44440);
	serv_addr.sin_addr.s_addr = inet_addr("192.168.100.54");

	bindserv = bind(socketserv, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if ( bindserv == -1 )
        {
                perror("Bind");
                exit(-1);
        }
        else
        {
                printf("[+] Bind To Port Successful \n");
        }

	listenserv = listen(socketserv, 3);
	if ( listenserv == -1 )
        {
                perror("Listen");
                exit(-1);
        }
        else
        {
                printf("[+] Listening... \n");
        }

	len = sizeof(cli_addr);
	acceptserv = accept(socketserv, (struct sockaddr *)&cli_addr, &len);

	bzero(buffer, 1024);
	strcpy(buffer, "Hello World!!!");
        send_cli = send(acceptserv, buffer, strlen(buffer), 0);
	printf("Message sent to client: %s\n", buffer);

	closing = close(socketserv);
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
