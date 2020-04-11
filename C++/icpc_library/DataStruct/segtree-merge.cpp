int a[maxn],cnt,root[maxn];
vector<int> g[maxn];
ll ans[maxn];
class dsegtree{public:
#define nd  node[now]
#define ndl node[node[now].son[0]]
#define ndr node[node[now].son[1]]
  struct dsegnode {
    int son[2],cnt,id,ans;
  }node[maxn*50];
  void pushup(int now){
    if(ndl.cnt>ndr.cnt){
      nd.cnt=ndl.cnt;
      nd.id=ndl.id;
      nd.ans=ndl.ans;
    }else if(ndr.cnt>ndl.cnt){
      nd.cnt=ndr.cnt;
      nd.id=ndr.id;
      nd.ans=ndr.ans;
    }else {
      nd.cnt=ndr.cnt;
      nd.id=ndr.id;
      nd.ans=ndr.ans+ndl.ans;
    }
  }
  void update(int l,int r,int pos,int &now){
    if(!now) now=++cnt;
    if(l==r){
      nd.id=nd.ans=l;
      nd.cnt+=1;
      return ;
    }
    int mid=(l+r)>>1;
    if(pos<=mid) update(l,mid,pos,nd.son[0]);
    else update(mid+1,r,pos,nd.son[1]);
    pushup(now);
  }
  int merge(int now,int b,int l,int r){
    if(!now||!b) return now^b;
    if(l==r){
      nd.id=nd.ans=l;
      nd.cnt+=node[b].cnt;
      return now;
    }
    nd.son[0]=merge(nd.son[0],node[b].son[0],l,(l+r)/2);
    nd.son[1]=merge(nd.son[1],node[b].son[1],(l+r)/2+1,r);
    pushup(now);
    return now;
  }
}tree;
void dfs(int now,int fa){
  for(int to:g[now]){
    if(to==fa) continue;
    dfs(to,now);
    tree.merge(root[now],root[to],1,1e5);
  }
  tree.update(1,1e5,a[now],root[now]);
  ans[now]=tree.node[root[now]].ans;
}
int main() {
  cin>>n;
  rep(i,1,n){
     cin>>a[i];
     root[i]=i;
  }
  cnt=n;
  rep(i,2,n){
    int a,b;cin>>a>>b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  dfs(1,0);
  rep(i,1,n) cout<<ans[i]<<' ';
}
