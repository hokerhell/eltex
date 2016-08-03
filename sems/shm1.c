#include "shm1.h"
int main() 
{
	key_t key;
	int semid, shmid;
	struct sembuf sops;
	char *shmaddr;
	char str[256];
	key=12345;
	if ((shmid = shmget(key, 256, IPC_CREAT | 0666)) < 0) { perror("shmget"); return 1; }
	if ((shmaddr = (char*)shmat(shmid, NULL, 0)) == (void*)-1) { perror("shmat"); return 1; }
	semid = semget(key, 1, IPC_CREAT | 0666);
	semctl(semid, 0, IPC_SET, 0);
	sops.sem_num = 0;
	sops.sem_flg = 0;
	do {
		do {
			printf("PROC#1> Input string (enter Q to exit):");
		} while (fgets(str, 255, stdin) == NULL);
		strcpy(shmaddr, str);
		printf("PROC#1> String copied to the shared buffer\n");
		sops.sem_op = 1; 
		semop(semid, &sops, 1);
		printf("PROC#1> Access released to the shared buffer\n");
	} while (str[0] != 'Q');
	shmdt(shmaddr); 
	semctl(semid,0,IPC_RMID, 0); 
	shmctl(shmid,IPC_RMID,NULL); 
	return 0;
}