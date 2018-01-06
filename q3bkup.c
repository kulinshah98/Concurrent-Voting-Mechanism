#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>

int n;

int tmp[105];
typedef struct booth{
  int num_voters,num_evms,cap_evm,evm[105],count[105];
  pthread_mutex_t mutex;
  pthread_attr_t attr;
  pthread_t voter_tid[105],evm_tid[105];
}booth;

booth bth[15];


void *voter(void *arg)
{
  int i,voter_num;
  pthread_t id;
  id=pthread_self();
  int bth_num=*(int *)arg;
  for(i=0;i<bth[bth_num].num_voters;i++)
  {
    if(id==bth[bth_num].voter_tid[i])
    {
      voter_num=i;
      break;
    }
  }
  //printf("Voter - %d %d %d\n",bth_num,voter_num,bth[bth_num].evm[voter_num]);
  int tmp;
  while(bth[bth_num].evm[voter_num]==-1)
  {
    tmp=rand()%3;
    sleep(tmp);
  }
  bth[bth_num].count[bth[bth_num].evm[voter_num]]--;
  return NULL;
}

void fprintPt(pthread_t id)
{
    size_t i;
    for (i = sizeof(i); i; --i)
    	printf("%02x", *(((unsigned char*) &id) + i - 1));
}

void *evm_func(void *arg)
{
  int i,evm_num;
  pthread_t id=pthread_self();
  int bth_num=*(int *)arg;
  for(i=0;i<bth[bth_num].num_evms;i++)
  {
    if(id==bth[bth_num].evm_tid[i])
    {
      evm_num=i;
      break;
    }
  }
//  printf("EVM - %d %d\n",bth_num,evm_num);
  int tmp,counter;
  while(1)
  {
    tmp=rand()%3;
    sleep(tmp);
    //printf("%d\n",bth[bth_num].count[evm_num]);
    if(bth[bth_num].count[evm_num]==0)
    {
  //    printf("*******%d %d\n",bth_num,evm_num);
      pthread_mutex_lock(&bth[bth_num].mutex);
    //  printf("%d %d\n",bth_num,evm_num);
      counter=rand()%(bth[bth_num].cap_evm)+1;
      printf("EVM %d at booth %d is free with slots=%d\n",evm_num,bth_num,counter);
      bth[bth_num].count[evm_num]=counter;
      for(i=0;i<bth[bth_num].num_voters;i++)
      {
        if(bth[bth_num].evm[i]==-1)
        {
          bth[bth_num].evm[i]=evm_num;
          printf("Voter %d of %d booth is allocated to %d\n",i,bth_num,evm_num);
          //printf("%d %d %d\n",bth_num,i,evm_num);
          printf("Voter %d of %d booth voted in evm %d\n",i,bth_num,evm_num);
          counter--;
          if(counter==0)
          {
            break;
          }
        }
      }
      bth[bth_num].count[evm_num] = bth[bth_num].count[evm_num] - counter;
      pthread_mutex_unlock(&bth[bth_num].mutex);
      if(i==bth[bth_num].num_voters)
      {
        break;
      }
    }
  }
  return NULL;
}

void initialise()
{
  int i,j;
  for(i=0;i<n;i++)
  {
    pthread_mutex_init(&bth[i].mutex, NULL);
  }
  for(i=0;i<n;i++)
  {
    pthread_attr_init(&bth[i].attr);
  }
  for(i=0;i<n;i++)
  {
    for(j=0;j<bth[i].num_voters;j++)
    {
      tmp[i]=i;
      pthread_create(&bth[i].voter_tid[j],&bth[i].attr,voter,&tmp[i]);
      bth[i].evm[j]=-1;
      //printf("--%d\n",bth[i].evm[j]);
    }
    for(j=0;j<bth[i].num_evms;j++)
    {
      tmp[i]=i;
      pthread_create(&bth[i].evm_tid[j],&bth[i].attr,evm_func,&tmp[i]);
      bth[i].count[i]=0;
    }
  }
}

int main()
{
  int i;
  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
    scanf("%d%d%d",&bth[i].num_voters,&bth[i].num_evms,&bth[i].cap_evm);
  }
  initialise();
  sleep(10);
  return 0;
}
