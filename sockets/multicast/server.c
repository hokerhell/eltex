#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define GRP_PORT    1337
#define GRP_ADDR    "239.0.0.11"
#define MSG_MAXLEN  512

int main(int argc, char const *argv[])
{
	int sock, str_size;
	struct sockaddr_in addr_clt;
	char str[MSG_MAXLEN];
	socklen_t addr_len;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) { perror("socket"); exit(-1); }
	addr_clt.sin_family = AF_INET;
	addr_clt.sin_port = htons(GRP_PORT);
	addr_clt.sin_addr.s_addr = inet_addr(GRP_ADDR);
	addr_len = sizeof(addr_clt);
	while (1)
	{
		gets(str);
		sendto(sock, str, MSG_MAXLEN, 0, (struct sockaddr *)&addr_clt, addr_len);
		if (!strcmp(str, "exit"))
			break;
	}
	close(sock);
	exit(0);
}