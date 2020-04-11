int sg[maxn][maxn];
int getmex(bool *vis,int n){
  int t=0;
  while(vis[t]) ++t;
  return t;
}
int getsg(int n,int m){
  if(~sg[n][m]) return sg[n][m];
  if(n<=m) return sg[n][m]=1;
  bool vis[n+1]={0};
  rep(i,1,m)vis[getsg(n-i,m)]=1;
  return sg[n][m]=getmex(vis,n);
}
int main() {
  memset(sg,-1,sizeof sg);
  cin>>casn;
  while(casn--){
    cin>>n>>m;
    if(getsg(n,m)) cout<<"first\n";
    else cout<<"second\n";
  }
  return 0;
}
