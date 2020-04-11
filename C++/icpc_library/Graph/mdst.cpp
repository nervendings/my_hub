//@定根最小树形图@
struct node{int a,b,c;}e[maxm];
int in[maxn],pre[maxn],vis[maxn],id[maxn];
ll mdst(){
  ll ans=0;int cnt=0,a,b,laz;
  while(1){
    rep(i,1,n) in[i]=INF,id[i]=vis[i]=0;
    rep(i,1,m) if(e[i].a^e[i].b&&e[i].c<in[e[i].b])
      pre[e[i].b]=e[i].a,in[e[i].b]=e[i].c;
    in[k]=0;
    rep(i,1,n){
      if(in[i]==INF) return -1;
      ans+=in[i];
      for(a=i;a^k&&vis[a]^i&&!id[a];a=pre[a])vis[a]=i;
      if(a^k&&!id[a]){
        id[a]=++cnt;
        for(b=pre[a];a^b;b=pre[b])id[b]=cnt;
      }
    }
    if(!cnt) return ans;
    rep(i,1,n) if(!id[i]) id[i]=++cnt;
    rep(i,1,m) {
      laz=in[e[i].b];
      if((e[i].a=id[e[i].a])^(e[i].b=id[e[i].b]))
        e[i].c-=laz;
    }
    n=cnt;k=id[k],cnt=0;
  }
}
int main() {IO;
  cin>>n>>m>>k;
  rep(i,1,m)cin>>e[i].a>>e[i].b>>e[i].c;
  cout<<mdst()<<endl;
}
