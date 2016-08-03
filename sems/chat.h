#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <pthread.h>
typedef struct
{
	long mtype;
	char client[100];
	char message[255];
} mess_t;