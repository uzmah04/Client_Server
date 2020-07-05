#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
	int socketCli, len_cli, connect_serv, receive_serv, closing;

	struct sockaddr_in serv_addr;

	char buffer[1024];

	socketCli = socket(AF_INET, SOCK_STREAM, 0);

	memset(&(serv_addr.sin_zero), '\0', 8);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(44440);
	serv_addr.sin_addr.s_addr = inet_addr("192.168.100.54");

	len_cli = sizeof(serv_addr);
	connect_serv = connect(socketCli, (struct sockaddr *)&serv_addr, len_cli);

	receive_serv = recv(socketCli, buffer, 1024, 0);

	printf("Message: %s \n", buffer);

	closing = close(socketCli);

	return 0;
}
