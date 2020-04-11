//@可持久化并查集,主席树实现@
int rt[maxn];
int l0,r0;
class pdsu{public:
#define nd node[now]
#define ndp node[pre]
#define mid (s+t)/2
  int cnt;
  struct segnode{int l,r,fa,dep;}node[maxn*30];
  void init(int n){
    l0=1,r0=n,cnt=0;
    makearray();
  }
  void makearray(int &now=rt[0],int s=l0,int t=r0){
    now=++cnt;nd={0,0,s,0};
    if(s==t)return;
    makearray(nd.l,s,mid);makearray(nd.r,mid+1,t);
  }
  void merge(int pre,int &now,int pos,int fa,int s=l0,int t=r0){
    now=++cnt;nd=ndp;
    if(s==t){nd.fa=fa;return;}
    if(pos<=mid) merge(ndp.l,nd.l,pos,fa,s,mid);
    else merge(ndp.r,nd.r,pos,fa,mid+1,t);
  }
  void update(int now,int pos,int s=l0,int t=r0){
    if(s==t) {nd.dep++;return;}
    if(pos<=mid) update(nd.l,pos,s,mid);
    else update(nd.r,pos,mid+1,t);
  }
  int query(int now,int pos,int s=l0,int t=r0){
    if(s==t) return now;
    if(pos<=mid) return query(nd.l,pos,s,mid);
    else return query(nd.r,pos,mid+1,t);
  }
//@找到第ver个版本的集合根:@
  int find(int ver,int pos){
    int now=query(ver,pos);
    if(nd.fa==pos) return now;
    return find(ver,nd.fa);
  }
//@在ver1的基础上,合并a,b集合,得到ver2:@
  void unite(int ver1,int ver2,int a,int b){
      rt[ver2]=rt[ver1];
      int fa=find(rt[ver2],a),fb=find(rt[ver2],b);
      if(node[fa].fa==node[fb].fa) return;
      if(node[fa].dep>node[fb].dep) swap(fa,fb);
      merge(rt[ver1],rt[ver2],node[fa].fa,node[fb].fa);
      if(node[fa].dep==node[fb].dep) 
        update(rt[ver2],node[fb].fa);
  }
//@复制ver1的状态到ver2,并查询a,b是否为同集合@
  bool same(int ver1,int ver2,int a,int b){
    rt[ver2]=rt[ver1];
    int fa=find(rt[ver2],a),fb=find(rt[ver2],b);
    return node[fa].fa==node[fb].fa;
  }
//@令ver2的状态回到ver1:@
  void popback(int ver1,int ver2){
    rt[ver2]=rt[ver1];
  }
#undef mid
}dsu;
