#include "chat.h"
int qmid;
int	lengthm;
int stexit=0;
mess_t received;

void *funcchat()
{
	while(1)
	{
		msgrcv(qmid, &received, lengthm, 1, 0);
		printf("[%s] : %s\n", received.client, received.message);
		if(strcmp(received.message,"quit") == 0) {
			stexit++;
			break;
		}
		sleep(1);
	}
}

int main(int argc, char const *argv[])
{
	int qsid, semid;
	key_t msgkeym;
	key_t msgkeys; 
	key_t key=12345;
	mess_t sysm;
	struct sembuf sops;
	char str[255];
	pthread_t chat;
	lengthm = sizeof(mess_t) - sizeof(long);
	msgkeym = ftok(".",'m');
	msgkeys = ftok(".",'s');
	semid = semget(key, 1, 0777);
	sops.sem_num = 0;
	sops.sem_flg = 0;
	sops.sem_op = 1;
	semop(semid, &sops,1);
	if((qmid = msgget(msgkeym, 0777)) == -1) perror("msgget error:");
	if((qsid = msgget(msgkeys, 0777)) == -1) perror("msgget error:");
	printf("type ur name\n");
	gets(str);
	strcpy(sysm.client,str);
	sysm.mtype=1;
	if((pthread_create(&chat, NULL, funcchat, NULL)) == -1) perror("pthread create error:");
	while(1)
	{	
		if(stexit == 1) break;
		gets(str);
		strcpy(sysm.message, str);
		msgsnd(qsid, &sysm, lengthm, 0);	
		if (strcmp(str,"quit") == 0) break;
	}
	sops.sem_op = -1;
	semop(semid, &sops,1);
	if((pthread_cancel(chat)) == -1) perror("pthread cancel error:");
	return 0;
}