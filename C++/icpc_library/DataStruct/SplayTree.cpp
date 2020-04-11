int root;//@树根@
class splaytree{public:
  int fa[maxn],son[maxn][2],sz[maxn],val[maxn],cnt[maxn];
  int tot;//@根权值重复次数子树大小@
  inline void pushup(int now){
    sz[now]=sz[son[now][0]]+sz[son[now][1]]+cnt[now];
  }//@更新当前节点信息@
  inline bool getson(int now) {return now==son[fa[now]][1];}//@真为右儿子@
  inline void clear(int now){
    fa[now]=son[now][0]=son[now][1]=sz[now]=val[now]=cnt[now]=0;
  }//@清空节点@
  inline void rotate(int now){
    int f=fa[now],gf=fa[fa[now]],flag=getson(now);
    son[f][flag]=son[now][flag^1];
    fa[son[now][flag^1]]=f;
    son[now][flag^1]=f;
    fa[f]=now;fa[now]=gf;
    if(gf) son[gf][f==son[gf][1]]=now;
    pushup(now);pushup(f);
  }//@旋转一层@
  void splay(int now){
    for(int f=fa[now];f=fa[now],f;rotate(now))
      if(fa[f]) rotate(getson(now)==getson(f)?f:now);
    root=now;
  }//@旋转到根@
  void insert(int x,int now=root,int f=0){
    if(!now){
      now=++tot;
      val[now]=x,cnt[now]++;
      if(!root)root=now;
      pushup(now);
      if(f){
        fa[now]=f;
        son[f][val[f]<x]=now;
        pushup(f);splay(now);
      }
    }else if(val[now]==x){
      ++cnt[now];
      pushup(now);pushup(f);
      splay(now);
    }else insert(x,son[now][val[now]<x],now);
  }//@插入新点@
  int getrank(int x,int now=root,int ans=0){
    while(1){
      if(x<val[now]) now=son[now][0];
      else {
        ans+=sz[son[now][0]];
        if(x==val[now]) return splay(now),ans+1;
        ans+=cnt[now];now=son[now][1];
      }
    }
  }//@多少个元素小于@x
  int get(int k,int now=root){
    while(1){
      if(son[now][0]&&k<=sz[son[now][0]]) now=son[now][0];
      else {
        k-=cnt[now]+sz[son[now][0]];
        if(k<=0) return val[now];
        now=son[now][1];
      }
    }
  }//@查询元素@
  int pre(){
    int now=son[root][0];
    while(son[now][1]) now=son[now][1];
    return now;
  }//@前驱@
  int nxt(){
    int now=son[root][1];
    while(son[now][0]) now=son[now][0];
    return now;
  }//@后缀@
  int lower(int x){
    insert(x);
    int ans=val[pre()];
    erase(x);return ans;
  }//@查询前驱@
  int upper(int x){
    insert(x);
    int ans=val[nxt()];
    erase(x);return ans;
  }//@查询后缀@
  void erase(int x){
    getrank(x);
    if(cnt[root]>1){
      --cnt[root];pushup(root);
    }else if(!son[root][0]&&!son[root][1]){
      clear(root);root=0;
    }else if(!son[root][0]||!son[root][1]){
      int t=root;
      if(!son[root][0]) root=son[root][1];
      else root=son[root][0];
      fa[root]=0;clear(t);
    }else {
      int now=pre(),t=root;
      splay(now);
      fa[son[t][1]]=now;
      son[now][1]=son[t][1];
      clear(t);pushup(root);
    }
  }//@删除元素@
}tree;
int main() {
  cin>>n;
  while(n--){
    int opt,x;cin>>opt>>x;
    if(opt==1) tree.insert(x);
    if(opt==2) tree.erase(x);
    if(opt==3) cout<<tree.getrank(x)<<endl;
    if(opt==4) cout<<tree.get(x)<<endl;
    if(opt==5) cout<<tree.lower(x)<<endl;
    if(opt==6) cout<<tree.upper(x)<<endl;
  }
	return 0;
}
