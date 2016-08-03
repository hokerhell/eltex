#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define NUM_CASSES	4
#define NUM_BUYERS	8

typedef struct
{
	int id;
	int resource;
	pthread_mutex_t mutex;
}CASS;

typedef struct
{
	int resource;
	pthread_t buyer;	
}BUYER;

typedef struct 
{
	int id;
	CASS cass_array[NUM_CASSES];
	BUYER buyer_array[NUM_BUYERS];
}ALL;

ALL ally;
int GetRand(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

void *FuncBuyer(void *t)
{
	ALL *my_all;
	my_all = (ALL *) t;
	int k,c;
	int ad = my_all->id;
	while (my_all->buyer_array[ad].resource<500)
	{
		c=GetRand(0,NUM_CASSES-1);
		if( pthread_mutex_trylock(&my_all->cass_array[c].mutex) == EBUSY )
			return;
		if((my_all->cass_array[c].resource-100)>=0)
		{
			k=GetRand(0,100);
			my_all->buyer_array[ad].resource+=k;
			my_all->cass_array[c].resource-=k;
			printf("Buyer (%d)[%d]: Take %d from cass %d(%d)\n", ad+1,
					my_all->buyer_array[ad].resource,k, c + 1, my_all->cass_array[c].resource);
		}
		pthread_mutex_unlock(&my_all->cass_array[c].mutex);
		sleep(3);
	}
	printf("Buyer (%d)[%d]: I'm done!!!\n", ad+1, my_all->buyer_array[ad].resource);
	pthread_exit(0);
}

void *FuncLoader(void *t)	
{
	ALL *my_all;
	my_all = (ALL *) t;
	int i,k;
	while (1)
	{
		for(i = 0; i < NUM_CASSES; i++)
		{
			if(i == NUM_CASSES)
				i = 0;
			if( pthread_mutex_trylock(&my_all->cass_array[i].mutex) == EBUSY )
				return;
			if(my_all->cass_array[i].resource<400)
			{
				k=GetRand(100,200);
				my_all->cass_array[i].resource+=k;
			}	
			printf("Load %d  to cass %d(%d)\n",k,my_all->cass_array[i].id+1, my_all->cass_array[i].resource);
			pthread_mutex_unlock(&my_all->cass_array[i].mutex);
			sleep(3);
		}
	}
	pthread_exit(0);
}

int main (int argc, char *argv[])
{
	ALL *all;
	all=&ally;
	pthread_t loader;
	int t,rc;
	for(t=0;t<NUM_CASSES;t++)
	{
		all->cass_array[t].resource=400;
		all->cass_array[t].id=t;
		pthread_mutex_init(&all->cass_array[t].mutex, NULL);
	}	
	for(t=0;t<NUM_BUYERS;t++)
	{
		all->buyer_array[t].resource=0;
		all->id=t;
		pthread_create(&all->buyer_array[t].buyer, NULL, FuncBuyer, all);
		sleep(1);
	};
		pthread_create(&loader, NULL, FuncLoader, all);
	for(t = 0; t < NUM_BUYERS; t++)
		pthread_join(all->buyer_array[t].buyer, 0);
	pthread_cancel(loader);
	return 0;
}