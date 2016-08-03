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
#define MSG_MAXLEN  256

int main(int argc, char const *argv[])
{
	int sock,str_size;
	struct sockaddr_in addr_srv, addr_clt;
	char str[MSG_MAXLEN];
	socklen_t addr_len;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) { perror("socket"); exit(-1); }
	addr_srv.sin_family = AF_INET;
	addr_srv.sin_port = htons(SRV_PORT);
	addr_srv.sin_addr.s_addr = inet_addr(SRV_ADDR);
	if (bind(sock, (struct sockaddr *)&addr_srv, sizeof(addr_srv)) == -1){ perror("bind"); exit(-1); }
	addr_len = sizeof(addr_clt);
	while (1)
	{
		if(recvfrom(sock, str, MSG_MAXLEN, 0, (struct sockaddr *)&addr_clt, &addr_len) == -1)
			break;
		if (!strcmp(str, "exit"))
			break;
		printf("%s\n",str);
		sendto(sock, str, MSG_MAXLEN, 0, (struct sockaddr *)&addr_clt, addr_len);
	}
	close(sock);
	exit(0);
}