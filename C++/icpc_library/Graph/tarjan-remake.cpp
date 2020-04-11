int casn,n,m,k;
struct node {int to,next;}e[maxm];int head[maxn],nume;
inline void add(int a,int b){e[++nume]=(node){b,head[a]};head[a]=nume;}
namespace tarjan{
  int stk[maxn],top,cnt,dfn[maxn],low[maxn],numc,belong[maxn],vis[maxn];
  vector<int>g[maxn];
  void tdfs(int now,int fa){
    dfn[now]=low[now]=++cnt;
    stk[top++]=now,vis[now]=1;
    for(int i=head[now];i;i=e[i].next){
      int to=e[i].to;
      if(!dfn[to]){tdfs(to,now);low[now]=min(low[now],low[to]);}
      else if(vis[to]) low[now]=min(low[now],dfn[to]);
    /*
      if(to==fa) continue;
      if(!dfn[to]){tdfs(to,now);low[now]=min(low[now],low[to]);}
      else low[now]=min(low[now],dfn[to]);
    */
    }
    if(low[now]==dfn[now]){
      numc++;
      int to;
      do{to=stk[--top];
        belong[to]=numc;
        vis[to]=0;
      }while(to!=now);
    }
  }
  void makegraph(int n){
    for(int i=1;i<=n;i++) if(!dfn[i]) tdfs(i,i);
    rep(i,1,n){
      int a=belong[i];
      for(int j=head[i];j;j=e[j].next){
        int b=belong[e[j].to];
        if(a!=b){
          g[a].emplace_back(b);
          g[b].emplace_back(a);
        }
      }
    }
  }
}
