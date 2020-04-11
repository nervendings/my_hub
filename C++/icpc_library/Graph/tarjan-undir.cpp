int stk[maxn],top,cnt,dfn[maxn],low[maxn],numc,belong[maxn],vis[maxn],sz[maxn];
struct node {int to,next;}e[maxm];int head[maxn],nume;
inline void add(int a,int b){e[++nume]=(node){b,head[a]};head[a]=nume;}
void tdfs(int now,int pre){
  dfn[now]=low[now]=++cnt;
  stk[top++]=now,vis[now]=1;
  for(int i=head[now];i;i=e[i].next){
    int to=e[i].to;
    if(to==pre) continue;
    if(!dfn[to]){tdfs(to,now);low[now]=min(low[now],low[to]);}
    else low[now]=min(low[now],dfn[to]);
  }
  if(low[now]==dfn[now]){
    numc++;
    int to;
    do{to=stk[--top];
      belong[to]=numc;
      sz[numc]++;
    }while(to!=now);
  }
}
