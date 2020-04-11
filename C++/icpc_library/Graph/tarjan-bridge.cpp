struct node{int to,nx;}e[maxm],e2[maxm];
int head[maxn],head2[maxn],nume,nume2;
bool bg[maxm];int dfn[maxn],low[maxn];
int numc,cnt,vis1[maxn],belong[maxn];
void add(int a,int b){
  e[++nume]={b,head[a]};head[a]=nume;
}
void add2(int a,int b){
  e2[++nume2]={b,head2[a]};head2[a]=nume2;
}
void tdfs(int now,int in){
  dfn[now]=low[now]=++cnt;
  for(int i=head[now];i;i=e[i].nx){
    int to=e[i].to;
    if(!dfn[to]) {
      tdfs(to,i);
      low[now]=min(low[now],low[to]);
      if(low[to]>dfn[now]) bg[i]=bg[i^1]=1;
    }else if(i!=(in^1))low[now]=min(low[now],dfn[to]);
  }
}
void dfs(int now){
  belong[now]=numc;
  for(int i=head[now];i;i=e[i].nx){
    int to=e[i].to;
    if(belong[to]||bg[i]) continue;
    dfs(to);
  }
}
pii dfs2(int now,int fa,int d=0){
  vis1[now]=1;pii x={d,now};
  for(int i=head2[now];i;i=e2[i].nx){
    int to=e2[i].to;
    if(to==fa) continue;
    pii t=dfs2(to,now,d+1);
    if(x<t) x=t;
  }
  return x;
}
int main() {
  cin>>casn;
  while(casn--){
    cin>>n>>m;
    rep(i,1,n){
      belong[i]=head[i]=head2[i]=0;
      low[i]=vis1[i]=dfn[i]=0;
    }
    rep(i,1,m*2+2)bg[i]=0;
    cnt=numc=0,nume=nume2=1;
    while(m--){
      int a,b;cin>>a>>b;
      add(a,b);add(b,a);
    }
    rep(i,1,n) if(!dfn[i]) tdfs(i,0);
    rep(i,1,n)
      if(!belong[i]) {
        numc++;dfs(i);
      }
    k=0;
    for(int i=2;i<=nume;i+=2){
      int a=e[i].to,b=e[i^1].to;
      if(belong[a]!=belong[b]){
        k++;
        add2(belong[a],belong[b]);
        add2(belong[b],belong[a]);
      }
    }
    int c=0;
    rep(i,1,numc){
      if(vis1[i]) continue;
      int t=dfs2(i,i).se;
      c=max(c,dfs2(t,t).fi);
    }
    cout<<k-c<<endl;
  }
}
