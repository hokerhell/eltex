#include "shm1.h"
int main()
{
	key_t key;
	int semid, shmid;
	struct sembuf sops;
	char *shmaddr, st = 0;
	char str[256];
	key=12345;
	if ((shmid = shmget(key, 256, 0666)) < 0) { perror("shmget"); return 1; }
	if ((shmaddr = (char*)shmat(shmid, NULL, 0)) == (void*)-1) { perror("shmat"); return 1; }
	semid = semget(key, 1, 0666);
	sops.sem_num = 0;
	sops.sem_flg = 0;
	do {
		printf("PROC#2> Waiting access to shared buffer\n");
		sops.sem_op = -1;
		semop(semid, &sops, 1);
		strcpy(str, shmaddr);
		printf("PROC#2> String: %s\n", str);
	} while (str[0] != 'Q');
	shmdt(shmaddr);
	return(0);
}