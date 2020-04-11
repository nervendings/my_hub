int num[maxn],dp[maxn],len;
int lwb(int now){
  int l=0,r=len,ans=0;
  while(l<r){
    int mid=(l+r)>>1;
    if(dp[mid]>=now) l=mid+1;
    else r=mid;
  }
  return l;
}
int lwb2(int now){
  int l=0,r=len;
  while(l<r){
    int mid=(l+r)>>1;
    if(dp[mid]>=now) r=mid;
    else l=mid+1;
  }
  return l;
}
int main(){
  cin>>n;
  for(int i=1;i<=n;i++) cin>>num[i];
  for(int i=1;i<=n;i++){
    if(dp[len]>=num[i]) dp[++len]=num[i];
    else dp[lwb(num[i])]=num[i];
  }
  cout<<len<<endl;
  len=0;
  memset(dp,0,sizeof dp);
  for(int i=1;i<=n;i++){
    if(dp[len]<num[i]) dp[++len]=num[i];
    else dp[lwb2(num[i])]=num[i];
  }
  cout<<len<<endl;
}
