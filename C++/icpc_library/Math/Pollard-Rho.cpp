//@得到n的一个随机因子,包括自身和1@
//@复杂度$O(n^{1/4})$@
//@要保证randint的随机范围大于等于测试数字@
ll mul_mod(ll a,ll b,ll c){return (__int128)a*b%c;}
int mul_mod(int a,int b,int c){return (ll)a*(ll)b%c;}
auto randint=bind(uniform_int_distribution<ll>(1e9,1e18),mt19937(rand()));
template<typename T> T pollard_rho(T n,T c=randint()) {
  T i=1,k=2,x=randint()%(n-1)+1,y=x,d;
  while(1){
    i++;
    x=(mul_mod(x,x,n)+c)%n;
    d=__gcd(n,y-x);
    if(d>1&&d<n)return d;
    if(y==x)return n;
    if(i==k){
      k<<=1;
      y=x;
    }
  }
}
//@分解因子,map中即为素因子从小到大,first为因子,second为次幂@
//@分解1000个1e18的数字约为600ms,10000个1e9的数字约为200ms@
map<ll,int> factor;
template<typename T>void get_factor(T n,T c=randint()) {
  if(n==1) return;
  if(miller_rabin(n)) {
    factor[n]++;
    return;
  }
  T p=n;
  while(p>=n) p=pollard_rho(p,c--);
  get_factor(p,c);
  get_factor(n/p,c);
}

//@新版实现 常数降低@
template<typename T>class Pollard_rho{public:
  ull s1,s2,s3,s4;
  Pollard_rho(){
    srand(time(0)+rand());
    s1=(ull)rand()*rand()*rand()*rand();
    s2=(ull)rand()*rand()*rand()*rand();
    s3=(ull)rand()*rand()*rand()*rand();
    s4=(ull)rand()*rand()*rand()*rand();
  }
  ull getinteger() {
    ull t=s1^(s1<<11);
    s1=s2;s2=s3;s3=s4;
    return s4=s4^(s4>>19)^t^(t>>8);
  }
  T randinteger(T l,T r){return T(getinteger()%((ull)r-l+1)+l);}
  T get_factor(T n,T c) {
  T i=1,k=2,x=randinteger(1,1e18)%(n-1)+1,y=x,d;
  while(1){
    i++;
    x=(mul_mod(x,x,n)+c)%n;
    d=__gcd(n,y-x);
    if(d>1&&d<n)return d;
    if(y==x)return n;
    if(i==k){
      k<<=1;
      y=x;
    }
  }
}
};
Pollard_rho<ll> rho;
