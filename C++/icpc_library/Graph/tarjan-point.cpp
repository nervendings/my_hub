void init(int n){
  for(int i=0;i<=n;i++){if(i!=0) f[i]=i;}
  memset(cut,false,n<<2);memset(low,0,n<<2);
  memset(dfn,0,n<<2);memset(head,0,n<<2);
  nume=cnt=0;
}
void tarjan(int u,int p){
  low[u]=dfn[u]=++cnt;
  int son=0;
  for(int i=head[u];i;i=e[i].next){
    int v=e[i].to;
    if(v==p)continue;
    if(!dfn[v]){
      son++;
      tarjan(v,u);
      low[u]=min(low[u],low[v]);
      if(u!=p&&low[v]>=dfn[u]){
        cut[u]=true;
      }
    } else low[u]=min(low[u],dfn[v]);
  }
  if(u==p&&son>1) cut[u]=true;
}
