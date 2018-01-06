

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
//printf("EVM - %d %d\n",bth_num,evm_num);
  int tmp,counter;
  while(1)
  {
    tmp=rand()%2;
    sleep(tmp);
  /*  pthread_mutex_lock(&bth[bth_num].mutex);
    printf("****OUT****%d %d\n",bth_num,evm_num);
    pthread_mutex_unlock(&bth[bth_num].mutex);*/
    if(bth[bth_num].count[evm_num]==0)
    {
  //    printf("*******%d %d\n",bth_num,evm_num);
      pthread_mutex_lock(&bth[bth_num].mutex);
      //printf("%d %d %d %d\n",bth_num,evm_num,bth[bth_num].num_voters_done,bth[bth_num].num_voters);
      if(bth[bth_num].num_voters_done==bth[bth_num].num_voters)
      {
        //pthread_mutex_lock(&bth[bth_num].mutex);
      //  printf("****C****%d %d\n",bth_num,evm_num);
      //  pthread_mutex_unlock(&bth[bth_num].mutex);
      //return NULL;
      pthread_mutex_unlock(&bth[bth_num].mutex);
        break;
      }
      counter=rand()%(bth[bth_num].cap_evm)+1;
      printf("EVM %d at booth %d is free with slots=%d\n",evm_num+1,bth_num+1,counter);
      //printf("%d %d %d %d\n",bth_num,evm_num,bth[bth_num].num_voters_done,bth[bth_num].num_voters);
      bth[bth_num].count[evm_num]=counter;
      for(i=0;i<bth[bth_num].num_voters;i++)
      {
        if(bth[bth_num].evm[i]==-1)
        {
          bth[bth_num].evm[i]=evm_num;
          printf("Voter %d at Booth %d got allocated EVM %d\n",i+1,bth_num+1,evm_num+1);
          counter--;
          if(counter==0)
          {
            break;
          }
        }
      }
      bth[bth_num].count[evm_num] = bth[bth_num].count[evm_num] - counter;
      bth[bth_num].num_voters_done+=bth[bth_num].count[evm_num];
      printf("EVM %d at Booth %d is moving for voting stage\n",evm_num+1,bth_num+1);
  //    printf("%d %d %d %d\n",bth_num,evm_num,bth[bth_num].num_voters_done,bth[bth_num].num_voters);
      pthread_mutex_unlock(&bth[bth_num].mutex);
      if(bth[bth_num].num_voters_done==bth[bth_num].num_voters)
      {
    //    pthread_mutex_lock(&bth[bth_num].mutex);
//        printf("****C****%d %d\n",bth_num,evm_num);
      //  pthread_mutex_unlock(&bth[bth_num].mutex);
      return NULL;
        break;
      }
    }
  }
  //printf("*******%d %d\n",bth_num,evm_num);
  return NULL;
}
