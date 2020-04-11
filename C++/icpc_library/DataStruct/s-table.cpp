const int maxp=21;
class stable{public:
  int logn[maxn],dp[maxp][maxn],pos[maxp][maxn];
  int *a;
  void init(int n=maxn-1){
    logn[2]=1;
    rep(i,3,n) logn[i]=logn[i>>1]+1;
  }
  void cal(int *_a,int n){//init(n)
    a=_a;
    rep(i,1,n) dp[0][i]=a[i],pos[0][i]=i;
    for(int j=1;(1<<j)<=n;j++) for(int i=1;i+(1<<j)-1<=n;++i)
      dp[j][i]=min(dp[j-1][i],dp[j-1][i+(1<<(j-1))]);
    for(int j=1;(1<<j)<=n;j++) for(int i=1;i+(1<<j)-1<=n;++i)
      if(a[pos[j-1][i]]<=a[pos[j-1][i+(1<<(j-1))]]) pos[j][i]=pos[j-1][i];
      else pos[j][i]=pos[j-1][i+(1<<(j-1))];
  }
  inline int query(int l,int r){
    int lg=logn[r-l+1];
    return min(dp[lg][l],dp[lg][r-(1<<lg)+1]);
  }
  inline int query_pos(int l,int r){
    int lg=logn[r-l+1];
    if(a[pos[lg][l]]<=a[pos[lg][r-(1<<lg)+1]])return pos[lg][l];
    else return pos[lg][r-(1<<lg)+1];
  }
}st;
