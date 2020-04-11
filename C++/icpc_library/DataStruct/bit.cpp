//@树状数组区间求和,单点修改@
template<typename T> class bit{public:
	T val[maxn];
	int lb(int x) {return x&(-x);}
  int len;
  void init(int _n){
    len=_n;
    fill_n(val+1,len+1,INF);
  }
  void update(int pos,T x){
    for(;pos>0&&pos<=n;pos+=lb(pos)) val[pos]+=x;
  }
  T psum(int pos){
    T sum=0;
    for(;pos>0;pos-=lb(pos)) sum+=val[pos];
    return sum;
  }
  T query(int l,int r){return psum(r)-psum(l-1);}
}tree;
//@树状数组前缀最小值,支持单点的取min覆盖操作@
template<typename T> class bit{public:
  T val[2*maxn];
  int lb(int x) {return x&-x;}
  int len;
  void init(int _n){
    len=_n;
    fill_n(val+1,len+1,INF);
  }
  void update(int pos,T x){
    for(;pos<=len;pos+=lb(pos)) val[pos]=min(val[pos],x);
  }
  T query(int pos){
    T res=INF;
    for(;pos;pos-=lb(pos)) res=min(val[pos],res);
    return res;
  }
};
bit<int> tree;
