class ufs{public:
  int fa[maxn],sz[maxn];
  stack<pii> stk;
  void init(int tot){
    rep(i,1,tot) fa[i]=i,sz[i]=1;
  }
  int find(int now){
    if(fa[now]==now) return now;
    return find(fa[now]);
  }
  bool unite(int a,int b){
    a=find(a),b=find(b);
    if(a==b)return 0;
    if(sz[a]<sz[b]) fa[a]=b,sz[b]+=sz[a],stk.push(make_pair(a,b));
    else fa[b]=a,sz[a]+=sz[b],stk.push(make_pair(b,a));
    return 1;
  }
  void undo(){
    if(!stk.empty()){
      auto now=stk.top();
      stk.pop();
      fa[now.fi]=now.fi;
      sz[now.se]-=sz[now.fi];
    }
  }
}dsu;
