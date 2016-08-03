#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SRV_PORT    1337
#define SRV_ADDR    "192.168.2.255"
#define MSG_MAXLEN  512

int main(int argc, char const *argv[])
{
	int sock, str_size, fl=1;
	struct sockaddr_in addr_srv, addr_clt;
	char str[MSG_MAXLEN];
	socklen_t addr_len;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) { perror("socket"); exit(-1); }
	addr_srv.sin_family = AF_INET;
	addr_srv.sin_port = htons(SRV_PORT);
	addr_srv.sin_addr.s_addr = inet_addr(SRV_ADDR);
	addr_len = sizeof(addr_clt);
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &fl, sizeof(int)) == -1)
	{
		perror("setsockopt");
		close(sock);
		exit(-1);   
    }
	while (1)
	{
		gets(str);
		sendto(sock, str, MSG_MAXLEN, 0, (struct sockaddr *)&addr_srv, addr_len);
		if (!strcmp(str, "exit"))
			break;
	}
	close(sock);
	exit(0);
}
