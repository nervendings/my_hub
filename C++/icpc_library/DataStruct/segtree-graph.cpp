int cnt;
class segtree{public:
#define nd  node[now]
#define ndl node[now<<1]
#define ndr node[now<<1|1]
  int flag;//1==intree,0==outtree
  struct segnode {
    int l,r,id;
    inline int mid(){return (r+l)>>1;}
    inline int len(){return r-l+1;}
  };
  segnode node[maxn<<2|3];
  vector<int> v;
  void init(int n,int flag){
    this->flag=flag;
    maketree(1,n);
  }
  void pushup(int now){
    if(!flag){
      g.add(nd.id,ndl.id,0);
      g.add(nd.id,ndr.id,0);
    }else {
      g.add(ndl.id,nd.id,0);
      g.add(ndr.id,nd.id,0);
    }
  }
  void maketree(int s,int t,int now=1){
    nd={s,t,++cnt};
    if(s==t){
      if(flag) g.add(s,nd.id,0);
      else g.add(nd.id,s,0);
      return ;
    }
    maketree(s,nd.mid(),now<<1);
    maketree(nd.mid()+1,t,now<<1|1);
    pushup(now);
  }
  vector<int>  query(int s,int t){v.clear();find(s,t);return v;}
  void find(int s,int t,int now=1){
    if(s<=nd.l&&t>=nd.r) {
      v.emplace_back(nd.id);
      return ;
    }
    if(s<=ndl.r) find(s,t,now<<1);
    if(t>ndl.r) find(s,t,now<<1|1);
  }
}intree,outree;
