#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/types.h>
#include<unistd.h>

int n;
pthread_mutex_t mutx[105];
pthread_attr_t attr[105];
pthread_t pro,con[105];
int buffer[105],no_of_unread[105],readpost[105][105],flag[105];

void initialise()
{
  int i;
  for(i=0;i<n;i++)
  {
    pthread_mutex_init(&mutx[i], NULL);
  }
  for(i=0;i<n;i++)
  {
    pthread_attr_init(&attr[i]);
  }
}


void *producer(void *param)
{
  int itm,i,j;
  while(1)
  {
    int tmp=rand()%15;
    tmp=tmp/10;
    sleep(tmp);
    //for(i=0;i<n;i++)
    //{
    tmp=rand()%n;
    i=tmp;
      if(no_of_unread[i]==0 && flag[i]==0)
      {
        pthread_mutex_lock(&mutx[i]);
        flag[i]=1;
        tmp=rand()%1000;
        buffer[i]=tmp;
        printf("Writer is writing in post number %d - %d\n",i,tmp);
        no_of_unread[i]=n;
        pthread_mutex_unlock(&mutx[i]);
      //  break;
      }
    //}
    tmp=0;
    for(i=0;i<n;i++)
    {
      if(flag[i]==1)
      {
        tmp++;
      }
    }
    if(tmp==n)
    {
      break;
    }
  }
  //printf("***\n");
  return NULL;
}

void *consumer(void *param)
{
  int itm,i,con_id;
  pthread_t id;
  id=pthread_self();
  for(i=0;i<n;i++)
  {
    if(id==con[i])
    {
      con_id=i;
    }
  }
  while(1)
  {
    int tmp=rand()%2;
  //  sleep(tmp);
    tmp=rand()%n;
        //printf("%d %d %d\n",i,tmp,readpost[i][tmp]);
    if(readpost[con_id][tmp]==0 && flag[tmp]==1)
    {
        pthread_mutex_lock(&mutx[tmp]);
        printf("Reader Number %d is reading post number %d - %d\n",con_id,tmp,buffer[tmp]);
        readpost[con_id][tmp]=1;
        no_of_unread[tmp]--;
        pthread_mutex_unlock(&mutx[tmp]);
        //break;
    }
    tmp=0;
    for(i=0;i<n;i++)
    {
      if(readpost[con_id][i]==1)
      {
        tmp++;
      }
    }
    //printf("%d %d\n",con_id,tmp);
    if(tmp==n)
    {
      break;
    }
  }
  //printf("**CON*\n");
  return NULL;
}

int main()
{
  int i,tm,j;
  scanf("%d",&n);
//  scanf("%d",&tm);
  for(i=0;i<n;i++)
  {
    flag[i]=0;
    no_of_unread[i]=0;
    for(j=0;j<n;j++)
    {
      readpost[i][j]=0;
    }
  }
  initialise();
  pthread_create(&pro,NULL,producer,NULL);
  for(i=0;i<n;i++)
  {
    pthread_create(&con[i],NULL,consumer,NULL);
  }
  pthread_join(pro,NULL);
  for(i=0;i<n;i++)
  {
    pthread_join(con[i],NULL);
  }
  //sleep(tm);
  printf("Exit programme\n");
  exit(0);
}
