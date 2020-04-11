//@底数不变,求值次数1e5以上的情况,可以加速10-100倍@
//@1e9: maxp 1e3,maxv 1e9,100倍@
//@1e18: maxp 32000,maxv 1e18,14倍左右@
const ll maxp=32000,maxv=1e18;
const ll maxw=log(maxv)/log(maxp)+1;
class basepow{public:
  ll pw[maxw][maxp];
  void init(ll base){
    base%=mod;
    rep(i,0,maxw-1)pw[i][0]=1;
    rep(i,1,maxp-1) pw[0][i]=(pw[0][i-1]*base)%mod;
    rep(i,1,maxw-1){
      pw[i][1]=pw[i-1][maxp-1]*pw[i-1][1]%mod;
      rep(j,2,maxp-1) pw[i][j]=pw[i][j-1]*pw[i][1]%mod;
    }
  }
  inline ll getpow(ll b,ll res=1,int cnt=0){
    while(b){
      res=res*pw[cnt++][b%maxp]%mod;
      b/=maxp;
    }
    return res;
  }
}p;
