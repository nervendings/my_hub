const int maxsz=3e5+7;//@maxsz素数表@
//1e7+19,2e7+3,3e7+23,4e5+9 @maxsz最好为素数@
//1e6+3,2e6+3,3e6+7,4e6+9,1e5+3,2e5+3,3e5+7
//@因为是vector不需要限制操作次数了@
//@count操作不增加新节点@
template<typename key,typename val>
class hash_map{public:
  struct node{key u;val v;int next;};
  vector<node> e;
  int head[maxsz],nume,numk,id[maxsz];
  int geths(key &u){return u;}
//@geths是把key映射到[0,maxsz-1]的函数@
  bool count(key &u){
    int hs=geths(u);
    for(int i=head[hs];i;i=e[i].next)
      if(e[i].u==u) return 1;
    return 0;
  }
  val& operator[](key &u){//@视情况加引用,可能引起CE@
    int hs=geths(u);
    for(int i=head[hs];i;i=e[i].next)if(e[i].u==u) return e[i].v;
    if(!head[hs])id[++numk]=hs;
    if(++nume>=e.size())e.resize(nume<<1);
    return e[nume]=(node){u,0,head[hs]},head[hs]=nume,e[nume].v;
  }
  void clear(){
    rep(i,0,numk)head[id[i]]=0;
    numk=nume=0;
  }
};
