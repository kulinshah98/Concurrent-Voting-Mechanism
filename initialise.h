#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>

typedef struct booth{
  int num_voters,num_evms,cap_evm,evm[105],count[105],num_voters_done;
  pthread_mutex_t mutex;
  pthread_attr_t attr;
  pthread_t voter_tid[105],evm_tid[105];
}booth;


extern int n,tmp[1005];

extern booth bth[205];
void initialise();
