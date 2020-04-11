class odt{public:
  struct segnode{
    int l,r;mutable int val;
    bool operator<(const segnode &b)const {return l<b.l;}
  };
  set<segnode> nd;
  void init(int n=maxn-5){nd.insert(1,n,0);}
  #define iter set<segnode>::iterator
  auto split(int pos){
    auto it=nd.lower_bound({pos,pos,0});
    if(it!=nd.end()&&it->l==pos) return it;
    it--;
    int l=it->l,r=it->r,val=it->val;
    nd.erase(it);nd.insert({l,pos-1,val});
    return nd.insert({pos,r,val}).fi;
  }
  void update(int l,int r,int val){
    auto itr=split(r+1);auto itl=split(l);
    nd.erase(itl,itr);nd.insert({l,r,val});
  }
  int query(int pos){
        auto it=nd.lower_bound({pos,pos,0});
         if(it!=nd.end()&&it->l==pos) return it->val;
         it--;return it->val;
    }
}tree;
