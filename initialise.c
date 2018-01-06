

int n,tmp[1005];

booth bth[205];
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
    bth[i].num_voters_done=0;
    for(j=0;j<bth[i].num_voters;j++)
    {
      tmp[i]=i;
      bth[i].evm[j]=-1;
      pthread_create(&bth[i].voter_tid[j],&bth[i].attr,voter,&tmp[i]);
      //printf("--%d\n",bth[i].evm[j]);
    }
    for(j=0;j<bth[i].num_evms;j++)
    {
      tmp[i]=i;
      bth[i].count[i]=0;
      pthread_create(&bth[i].evm_tid[j],&bth[i].attr,evm_func,&tmp[i]);
    }
  }
  for(i=0;i<n;i++)
  {
    for(j=0;j<bth[i].num_voters;j++)
    {
    //  printf("VOTER --- %d --- %d\n",i,j);
      pthread_join(bth[i].voter_tid[j],NULL);
    }
    for(j=0;j<bth[i].num_evms;j++)
    {
      //printf("EVM --- %d --- %d\n",i,j);
      pthread_join(bth[i].evm_tid[j],NULL);
    }
  }
}

void fprintPt(pthread_t id)
{
    size_t i;
    for (i = sizeof(i); i; --i)
    	printf("%02x", *(((unsigned char*) &id) + i - 1));
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
  //sleep(10);
  return 0;
}
