//@可持久化数组,主席树实现@
int a0[maxn];//@初始数组@
int rt[maxn];//@树根@
template<typename T>class parray{public:
#define nd node[now]
#define ndp node[pre]
#define mid (s+t)/2
  int cnt;
  static int l0,r0;//@数组区间@
  struct segnode{int l,r;T val;}node[maxn*20];
  void init(int s,int t,T a[]){
    l0=s,r0=t,cnt=0;
    makearray(a);
  }
  void makearray(T a[],int &now=rt[0],int s=l0,int t=r0){
    now=++cnt;
    if(s==t){nd.val=a[s];return;}
    makearray(a,nd.l,s,mid);makearray(a,nd.r,mid+1,t);
  }
  void update(int pre,int &now,int pos,T val,int s=l0,int t=r0){
    now=++cnt;nd=ndp;
    if(s==t){nd.val=val;return;}
    if(pos<=mid) update(ndp.l,nd.l,pos,val,s,mid);
    else update(ndp.r,nd.r,pos,val,mid+1,t);
  }
  T query(int now,int pos,int s=l0,int t=r0){
    if(s==t) return nd.val;
    if(pos<=mid) return query(nd.l,pos,s,mid);
    else return query(nd.r,pos,mid+1,t);
  }
#undef mid
};
parray<int>arr;
