class polysum {public:
  ll a[maxn],f[maxn],g[maxn],p[maxn],p1[maxn],p2[maxn],b[maxn],h[maxn][2],C[maxn];
  ll calcn(int d,ll *a,ll n) {//len=d get(an)
    if (n<=d) return a[n];
    p1[0]=p2[0]=1;
    rep(i,0,d) {
      ll t=(n-i+mod)%mod;
      p1[i+1]=p1[i]*t%mod;
    }
    rep(i,0,d) {
      ll t=(n-d+i+mod)%mod;
      p2[i+1]=p2[i]*t%mod;
    }
    ll ans=0;
    rep(i,0,d) {
      ll t=g[i]*g[d-i]%mod*p1[i]%mod*p2[d-i]%mod*a[i]%mod;
      if ((d-i)&1) ans=(ans-t+mod)%mod;
      else ans=(ans+t)%mod;
    }
    return ans;
  }
  void init(int maxm) {//init
    f[0]=f[1]=g[0]=g[1]=1;
    rep(i,2,maxm+4) f[i]=f[i-1]*i%mod;
    g[maxm+4]=pow_mod(f[maxm+4],mod-2);
    per(i,1,maxm+3) g[i]=g[i+1]*(i+1)%mod;
  }
  ll polysum(ll n,ll *a,ll m){//a[i]@会被修改@
    // @初始化预处理阶乘和逆元(取模乘法)@a[0].. a[m] \sum_{i=0}^{n-1} a[i]
    // len=m,psum_n
    a[m+1]=calcn(m,a,m+1);
    rep(i,1,m+1) a[i]=(a[i-1]+a[i])%mod;
    return calcn(m+1,a,n-1);
  }
  ll qpolysum(ll R,ll n,ll *a,ll m) { // a[0].. a[m] \sum_{i=0}^{n-1} a[i]*R^i
    if (R==1) return polysum(n,a,m);
    a[m+1]=calcn(m,a,m+1);
    ll r=pow_mod(R,mod-2),p3=0,p4=0,c,ans;
    h[0][0]=0;
    h[0][1]=1;
    rep(i,1,m+1) {
      h[i][0]=(h[i-1][0]+a[i-1])*r%mod;
      h[i][1]=h[i-1][1]*r%mod;
    }
    rep(i,0,m+1) {
      ll t=g[i]*g[m+1-i]%mod;
      if (i&1) p3=((p3-h[i][0]*t)%mod+mod)%mod,p4=((p4-h[i][1]*t)%mod+mod)%mod;
      else p3=(p3+h[i][0]*t)%mod,p4=(p4+h[i][1]*t)%mod;
    }
    c=pow_mod(p4,mod-2)*(mod-p3)%mod;
    rep(i,0,m+1) h[i][0]=(h[i][0]+h[i][1]*c)%mod;
    rep(i,0,m+1) C[i]=h[i][0];
    ans=(calcn(m,C,n)*pow_mod(R,n)-c)%mod;
    if (ans<0) ans+=mod;
    return ans;
  }
}
