class segtree{public:
#define nd  node[now]
#define ndl node[now<<1]
#define ndr node[now<<1|1]
  struct segnode {
    int l,r,mx;
    inline int mid(){return (r+l)>>1;}
    inline int len(){return r-l+1;}
  }node[maxn<<2|3];
  void maketree(int s,int t,int now=1){
    nd={s,t,0};
    if(s==t) return ;
    maketree(s,nd.mid(),now<<1);
    maketree(nd.mid()+1,t,now<<1|1);
  }
  void update(int pos,int x,int now=1){
    if(nd.l==nd.r){
       nd.mx=x;
       return ;
    }
    if(pos<=ndl.r)update(pos,x,now<<1);
    else update(pos,x,now<<1|1);
    nd.mx=max(ndl.mx,ndr.mx);
  }
  int query(int s,int t,int now=1){
    if(s<=nd.l&&t>=nd.r) return nd.mx;
    int a=0,b=0;
    if(s<=ndl.r) a=query(s,t,now<<1);
    if(t>ndl.r) b=query(s,t,now<<1|1);
    return max(a,b);
  }
}tree;

