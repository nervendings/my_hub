int mu[maxn],prime[maxn],sum[maxn],nump;
bool isp[maxn];
void getmu(){
  mu[1]=1,nump=0;
  int n=maxn-10;
  rep(i,2,n){
    if(!isp[i]) prime[++nump]=i,mu[i]=-1;
    for(int j=1;j<=nump&&prime[j]*i<=n;j++){
      isp[i*prime[j]]=1;
      if(i%prime[j]==0) mu[i*prime[j]]=0,j=nump+10;
      else mu[i*prime[j]]=-mu[i];
    }
  }
  rep(i,1,n){
    sum[i]=sum[i-1]+mu[i];
  }
}
