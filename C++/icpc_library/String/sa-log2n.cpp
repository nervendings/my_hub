namespace suffix{
char str[maxn];
int n,Sa[maxn],Rank[maxn],tp[maxn],k=0;
bool comp(int x,int y){
  if(rank[x]!=rank[y])return rank[x]<rank[y];
  int rx=x+k>n?-1:rank[x+k];
  int ry=y+k>n?-1:rank[y+k];rank
  return rx<ry;
}
bool judge(int x,int y){
  if(rank[x]==rank[y]){
    int rx=x+k>n?-1:rank[x+k];
    int ry=y+k>n?-1:rank[y+k];
    if(rx==ry) return 1;
  }else return 0;
}
void get_Sa(){
  rep(i,1,n) Sa[i]=i,rank[i]=str[i];
  for(k=1;k<=n;k<<=1){
    sort(Sa+1,Sa+n+1,comp);
    int fg=0;
    rep(i,1,n){
      if(!judge(Sa[i],Sa[i-1]))fg++;
      tp[Sa[i]]=fg;
    }
    rep(i,1,n) rank[i]=tp[i];
    if(fg>=n) break;
  }
  return ;
}
}
