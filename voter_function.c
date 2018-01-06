

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
  //  printf("***VOTER***%d %d\n",bth_num,voter_num);
  }
  //printf("Voter - %d %d %d\n",bth_num,voter_num,bth[bth_num].evm[voter_num]);
  int tmp;
  while(bth[bth_num].evm[voter_num]==-1)
  {
    tmp=rand()%3;
    sleep(tmp);
    //printf("***VOTER***%d %d\n",bth_num,voter_num);
  }
  bth[bth_num].count[bth[bth_num].evm[voter_num]]--;
  //printf("***VOTER***%d %d\n",bth_num,voter_num);
  return NULL;
}
