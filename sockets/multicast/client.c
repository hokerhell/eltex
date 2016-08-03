#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT    1337
#define GRP_ADDR    "239.0.0.11"
#define CLT_ADDR    "127.0.0.1"
#define MSG_MAXLEN  512

int main(int argc, char const *argv[])
{
	int sock;
	struct sockaddr_in addr_clt;
	struct ip_mreqn mreq;
	memset(&mreq, 0, sizeof(mreq));
	char str[MSG_MAXLEN];
	socklen_t addr_len;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) { perror("socket"); exit(-1); }
	addr_clt.sin_family = AF_INET;
	addr_clt.sin_port = htons(PORT);
	addr_clt.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_len = sizeof(addr_clt);
	if (bind(sock, (struct sockaddr *)&addr_clt, addr_len) == -1) { close(sock); perror("bind"); exit(-1); }
	mreq.imr_multiaddr.s_addr = inet_addr(GRP_ADDR);
	mreq.imr_address.s_addr = htonl(INADDR_ANY);
	if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) { perror("setsockopt"); exit(1); }
	while(1)
	{	
		if (recvfrom(sock, str, MSG_MAXLEN, 0, (struct sockaddr *)&addr_clt, &addr_len) == -1)
			break;
		printf("SERVER: %s\n", str);
		if (!strcmp(str, "exit"))
			break;
	}
	close(sock);
	exit(0);
}
