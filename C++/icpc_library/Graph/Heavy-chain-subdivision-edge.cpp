class graph{//@按边@
  struct node{int from,to,cost,next;}e[maxn<<1];
  int head[maxn],nume,cnt2;
  inline void add(int a,int b,int c){
    e[++nume]={a,b,c,head[a]};head[a]=nume;
  }
  int fa[maxn],sz[maxn],top[maxn],remp[maxn],ans[maxn];
  int son[maxn],in[maxn],cnt,deep[maxn];
  void dfs1(int now,int pre,int d){
    deep[now]=d;sz[now]=1;fa[now]=pre;
    for(int i=head[now];i;i=e[i].next){
      if(e[i].to==pre) continue;
      dfs1(e[i].to,now,d+1);
      sz[now]+=sz[e[i].to];
      if(sz[son[now]]<sz[e[i].to]) son[now]=e[i].to;
    }
  }
  void dfs2(int now,int pre,int st){
    top[now]=st;in[now]=++cnt;remp[cnt]=now;
    if(son[now]) dfs2(son[now],now,st);
    for(int i=head[now];i;i=e[i].next)
      if(e[i].to!=pre&&e[i].to!=son[now])
        dfs2(e[i].to,now,e[i].to);
  }
  int query(int a,int b){
    int sum=0;
    while(top[a]!=top[b]){
      if(deep[top[a]]<deep[top[b]]) swap(a,b);
      sum+=tree.query(in[top[a]],in[a]);
      a=fa[top[a]];
    }
    if(a==b)return sum;
    if(deep[a]>deep[b]) swap(a,b);
    sum+=tree.query(in[son[a]],in[b]);
    return sum;
  }
  void getchain(){dfs1(1,1,0);dfs2(1,1,1);}
}g;
int root=1;
class graph{public://@按点@
  struct node{int to,next;}e[maxn<<1];
  int head[maxn],nume,mp[maxn];
  inline void add(int a,int b){
    e[++nume]={b,head[a]};
    head[a]=nume;
  }
  int ltop[maxn],fa[maxn],deep[maxn];
  int sz[maxn],remp[maxn];
  int son[maxn],cnt;
  void init(int n){rep(i,1,n) head[i]=0;cnt=0,nume=1;}
  void dfs1(int now=root,int pre=root,int d=0){
    deep[now]=d,fa[now]=pre,sz[now]=1,son[now]=0;
    forn(i,now){
      int to=e[i].to;
      if(to!=pre) {
        dfs1(to,now,d+1);
        sz[now]+=sz[to];
        if(sz[to]>sz[son[now]]) son[now]=to;
      }
    }
  }
  void dfs2(int now=root,int pre=root,int sp=root){
    ltop[now]=sp;mp[now]=++cnt;remp[cnt]=now;
      if(son[now])  dfs2(son[now],now,sp);
      forn(i,now){
        int to=e[i].to;
        if(to!=son[now]&&to!=pre) dfs2(to,now,to);
      }
  }
  void getchain(){dfs1();dfs2();}
  int lca(int x,int y){
    for(;ltop[x]!=ltop[y];deep[ltop[x]]>deep[ltop[y]]?x=fa[ltop[x]]:y=fa[ltop[y]]);
    return deep[x]<deep[y]?x:y;
  }
  inline int getdis(int a,int b){return deep[a]+deep[b]-2*deep[lca(a,b)];}
  inline bool check(int a,int b){return dfn[a]<=dfn[b]&&dfn[a]+sz[a]-1>=dfn[b]+sz[b]-1;}
  //@基础部分@
  void update(int a,int b,int val){
    while(ltop[a]!=ltop[b]){
        if(deep[ltop[a]]<deep[ltop[b]])swap(a,b);
        tree.update(mp[ltop[a]],mp[a],val);
        a=fa[ltop[a]];
    }
      if(deep[a]>deep[b])swap(a,b);
      tree.update(mp[a],mp[b],val);
  }
  int query(int a,int b,int k){
    int sum=0;
    while(ltop[a]!=ltop[b]){
        if(deep[ltop[a]]<deep[ltop[b]])swap(a,b);
        sum+=tree.query(mp[ltop[a]],mp[a],k);
        a=fa[ltop[a]];
    }
      if(deep[a]>deep[b])swap(a,b);
      sum+=tree.query(mp[a],mp[b],k);
      return sum;
  }
}g;
