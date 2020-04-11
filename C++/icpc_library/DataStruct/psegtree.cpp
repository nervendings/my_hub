int rt[maxn];//@树根@
class ptree{public:
#define nd node[now]
#define ndp node[pre]
#define mid (s+t)/2
  int cnt;
  struct segnode{int l,r,sum;}node[maxn*30];
  void maketree(int s,int t,int &now=rt[0]){
    now=++cnt;nd={s,t,0};
    if(s==t) return ;
    maketree(s,mid,nd.l); maketree(mid+1,t,nd.r);
  }
  void update(int pos,int val,int s,int t,int &now,int pre){
    now=++cnt;nd=ndp;nd.sum+=val;
    if(s==t) return ;
    if(pos<=mid) update(pos,val,s,mid,nd.l,ndp.l);
    else update(pos,val,mid+1,t,nd.r,ndp.r);
  }
  ll query(int l,int r,int s,int t,int now,int pre){
    if(l<=s&&r>=t)return nd.sum-ndp.sum;
    ll sum=0;
    if(l<=mid) sum+=query(l,r,s,mid,nd.l,ndp.l);
    if(r>mid) sum+=query(l,r,mid+1,t,nd.r,ndp.r);
    return sum;
  }
#undef mid
}tree;
