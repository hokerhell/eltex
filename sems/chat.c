#include "chat.h"

int main(int argc, char const *argv[])
{
	int i, qmid, qsid, semid,rtrn;
	key_t msgkeym;
	key_t msgkeys;
	key_t key=12345;
	int	lengthm;
	mess_t received;
	mess_t sysm;
	lengthm = sizeof(mess_t) - sizeof(long);
	msgkeym = ftok(".",'m');
	msgkeys = ftok(".",'s');
	if((semid = semget(key, 1, IPC_CREAT | 0777)) == -1) perror("semget error:");
	semctl(semid,0,IPC_SET,0);
	printf("id messages:%d id systems:%d\n", qmid, qsid);
	if((qmid = msgget(msgkeym, IPC_CREAT | 0777)) == -1)  perror("msgget error:");
	if((qsid = msgget(msgkeys, IPC_CREAT | 0777)) == -1)  perror("msgget error:");
	while(1)
	{
		msgrcv(qsid, &sysm, lengthm, 1, 0);
		if(strcmp(sysm.message,"quit") == 0) 
		{
			rtrn=semctl(semid,0,GETVAL,0);
				for(i=0;i<rtrn+1;i++)
			msgsnd(qmid, &sysm, lengthm, 0);
			break;
		}
		
		rtrn=semctl(semid,0,GETVAL,0);
		for(i=0;i<rtrn;i++)
			msgsnd(qmid, &sysm, lengthm, 0);
	}
	if((msgctl(qmid, IPC_RMID, 0)) == -1) perror("msgctl error:");
	if((msgctl(qsid, IPC_RMID, 0)) == -1) perror("msgctl error:");
	if((semctl(semid,0,IPC_RMID, 0)) == -1) perror("semctl error:");
	return 0;
}