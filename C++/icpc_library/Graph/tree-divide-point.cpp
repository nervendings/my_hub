namespace graph{
  vector<int>g[maxn];
  int all,sz[maxn],root,maxt;
  bool vis[maxn];
  int dfs_root(int now,int fa){
    int cnt=1;
    for(auto to:g[now])if(to!=fa&&!vis[to])
      cnt+=dfs_root(to,now);
    int tmp=max(cnt-1,all-cnt);
    if(maxt>tmp) maxt=tmp,root=now;
    return sz[now]=cnt;
  }//@基础部分@
  int ans[maxn];
  void dfs_col(int now,int fa,int c){
    ans[now]=c;
    for(auto to:g[now])if(to!=fa&&!vis[to])
      dfs_col(to,now,c);
  }
  void dfs_dv(int now,int d=0){
    vis[now]=1;dfs_col(now,now,d);
    for(auto to:g[now]){
      if(vis[to]) continue;
      maxt=root=n+1;all=sz[to];
      dfs_root(to,now);dfs_dv(root,d+1);
    }
  }
  void solve(int n){
    all=maxt=root=n+1;
    dfs_root(1,1);
    all-=maxt;
    dfs_dv(root);
  }
} 
