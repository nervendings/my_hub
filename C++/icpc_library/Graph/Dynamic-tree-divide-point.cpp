//@动态点分治(点分树)@
template<const int N>class Graph{public:
  vector<int>g[N+10];
  bool vis[N+10];
  int all,sz[N+10],root,maxt,father[N+10];
  int _deep[N+10],_dfn[N+10],_cnt;
  int son[N+10];
  int _lca[N+10][int(log(N+10)/log(2))+1];
  int logn[N+10];
  void add(int a,int b){
    g[a].emplace_back(b);g[b].emplace_back(a);
  }
  int dfs_root(int now,int fa){
    int cnt=1;
    son[now]=0;
    for(auto to:g[now])if(to!=fa&&!vis[to]){
      int ch=dfs_root(to,now);
      son[now]=max(son[now],ch);
      cnt+=ch;
    }
    son[now]=max(son[now],all-cnt);
    if(son[now]<son[root]) root=now;
    return sz[now]=cnt;
  }
  void dfs_lca(int now,int fa){
    _dfn[now]=++_cnt;
    _lca[_cnt][0]=_deep[now]=_deep[fa]+1;
    for(auto to:g[now]) {
      if(to==fa) continue;
      dfs_lca(to,now);
      _lca[++_cnt][0]=_deep[now];
    }
  }
  void cal_st(){
    logn[0]=-1;
    rep(i,1,2e5+10) logn[i]=logn[i>>1]+1;
    rep(j,1,logn[_cnt])rep(i,1,_cnt-(1<<j)+1)
      _lca[i][j]=min(_lca[i][j-1],_lca[i+(1<<(j-1))][j-1]);
  }
  int _dis(int a,int b){
    a=_dfn[a],b=_dfn[b];
    if(a>b) swap(a,b);
    int len=logn[b-a+1];
    return min(_lca[a][len],_lca[b-(1<<len)+1][len]);
  }
  int dis(int a,int b){//@两点距离@
    int res=_deep[a]+_deep[b]-2*_dis(a,b);
    return res;
  }
  void dfs_cal(int now,int fa){
    for(auto to:g[now]){
      if(to==fa||vis[to]) continue;
      dfs_cal(to,now);
    }
  }
  void dfs_dv(int now,int fa){
    father[now]=fa;vis[now]=1;
    dfs_cal(now,0);
    for(auto to:g[now]){
      if(vis[to]) continue;
      all=sz[to],root=0;
      dfs_root(to,0);
      int tmp=root;
      dfs_dv(root,now);
    }
  }
  void init(int n){//@初始化@
    _cnt=0;
    dfs_lca(1,0);
    cal_st();
    son[0]=n;
    all=n;root=0;
    dfs_root(1,0);
    dfs_dv(root,0);
  }
  void update(int pos){
    for(int now=pos;father[now];now=father[now]){
      //@操作@
    }
  }
};
Graph<1e6> tree;
