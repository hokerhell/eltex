#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SRV_PORT    1488
#define SRV_ADDR    "127.0.0.1"
#define CNT_LISTEN  16
#define MSG_MAXLEN  256

int main(int argc, char const *argv[])
{
	int sock_clt, sock_srv, str_size;
	struct sockaddr_in addr_srv, addr_clt;
	char str[MSG_MAXLEN];
	socklen_t addr_len;
	if ((sock_srv = socket(AF_INET, SOCK_STREAM, 0)) == -1) { perror("socket"); exit(-1); }
	addr_srv.sin_family = AF_INET;
	addr_srv.sin_port = htons(SRV_PORT);
	addr_srv.sin_addr.s_addr = inet_addr(SRV_ADDR);
	if (bind(sock_srv, (struct sockaddr *)&addr_srv, sizeof(addr_srv)) == -1){ perror("bind"); exit(-1); }
	listen(sock_srv, CNT_LISTEN);
	addr_len = sizeof(addr_clt);
	if((sock_clt = accept(sock_srv, (struct sockaddr *)&addr_clt, &addr_len)) == -1) { perror("accept"); exit(-1); }
	printf("Connected: %d\n", sock_clt);
	while (1)
	{
		str_size = recv(sock_clt, str, MSG_MAXLEN, 0);
		if (str_size == -1)
			perror("recv");
		if (!strcmp(str, "exit"))
			break;
		else
			printf("%s\n", str);
			send(sock_clt, str, str_size, 0);
	}
	close(sock_srv);
	close(sock_clt);
	exit(0);
}