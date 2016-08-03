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
	int sock;	
	struct sockaddr_in addr;	
	char str[MSG_MAXLEN];
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) { perror("socket"); exit(-1); }
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SRV_PORT);
	addr.sin_addr.s_addr = inet_addr(SRV_ADDR);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1){ perror("connect"); close(sock); exit(-1); }
	while (1)
	{
		gets(str);
		send(sock, str, strlen(str) + 1, 0);
		if (!strcmp(str, "exit"))
			break;
		if (recv(sock, str, MSG_MAXLEN, 0))
		printf("recv: %s\n", str);
	}
	close(sock);
	exit(0);	 
}