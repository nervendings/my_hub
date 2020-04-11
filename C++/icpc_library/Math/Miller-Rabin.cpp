//@两种米勒罗宾素数筛实现@
//@第一种速度稍快,但实现麻烦,使用前需要先初始化@
//@单次复杂度约为1-maxpe中的素数个数*logn,maxpe不要小于50@
const int maxpe=100;
auto randint=bind(uniform_int_distribution<int>(1,1e9),mt19937(rand()));
ll mul_mod(ll a,ll b,ll c){return (__int128)a*(__int128)b%(__int128)c;}
int mul_mod(int a,int b,int c){return (ll)a*(ll)b%c;}
template<typename T> int pow_mod(int a,int b,int c){
  int res=1;
  while(b){
    if(b&1)res=mul_mod(res,a,c);
    a=mul_mod(a,a,c);
    b>>=1;
  }
  return res;
}
template<typename T> class miller_rabin{public:
  T prime[maxpe],cntp;
  void init(int n=maxpe-5){
    cntp=0;
    bool vis[n+1];
    rep(i,2,n)vis[i]=1;
    rep(j,2,n)if(vis[j]==1)
      for(int m=2;j*m<=n;++m)vis[j*m]=0;
    rep(i,2,n)if(vis[i]==1) prime[cntp++]=i;
  }
  bool _test(T n,T a,T d) {
    if(n==2||n==a) return true;
    if((n&1)==0) return false;
    while(!(d&1))d>>=1;
    T t=pow_mod(a,d,n);
    while(d!=n-1&&t!=1&&t!=n-1){
      t=mul_mod(t,t,n);
      d<<=1;
    }
    return (t==n-1||(d&1)==1);
  }
  bool test(T n) {
    if(n<2||n%2==0) return false;
    rep(i,0,cntp-1) if(!_test(n,prime[i],n-1)) return false;
    return true;
  }
};
miller_rabin<int> miller;
//@第二种实现@
//@速度稍慢,复杂度约为$logn*time$,time不要低于10@
const int test_time=20;
template<typename T> bool miller_rabin(T n) {
  if(n<3)return n==2;
  T a=n-1,b=0;
  while(a%2==0) a/=2,++b;
  for(int i=1,j; i<=test_time;++i){
    T x=randint()%(n-2)+2,v=pow_mod(x,a,n);
    if(v==1||v==n-1) continue;
    for(j=0;j<b;++j){
      v=mul_mod(v,v,n);
      if(v==n-1) break;
    }
    if(j>=b)return 0;
  }
  return 1;
}
