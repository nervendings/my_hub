namespace bm{
  const int maxl=1e4+10;
  ll res[maxl],base[maxl],_c[maxl],_md[maxl];
  vector<ll> md;
  ll inv(ll a,ll c=mod) {
    a%=c;if(a<0)a+=c;
    ll b=c,u=0,v=1;
    while(a) {
      ll t=b/a;b-=t*a;
      swap(a,b);u-=t*v;
      swap(u,v);
    }
    if(u<0)u+=c;
    return u;
  }
  void mul(ll *a,ll *b,int k) {
    for(int i=0;i<k+k;i++) _c[i]=0;
    for(int i=0;i<k;i++) if (a[i])
      for(int j=0;j<k;j++) _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
    for (ll i=k+k-1;i>=k;i--) if (_c[i])
      for(int j=0;j<md.size();j++)
        _c[i-k+md[j]]=(_c[i-k+md[j]]-_c[i]*_md[md[j]])%mod;
    for(int i=0;i<k;i++) a[i]=_c[i];
  }
  int solve(ll n,vector<ll> a,vector<ll> b) {
  //@a 系数 b 初值 b[n+1]=a[0]*b[n]+...@
  //@求出的是第n+1项 @
    ll ans=0,pnt=0;
    ll k=a.size();
    for(int i=0;i<k;i++) _md[k-1-i]=-a[i];_md[k]=1;
    md.clear();
    for(int i=0;i<k;i++) if (_md[i]!=0) md.push_back(i);
    for(int i=0;i<k;i++) res[i]=base[i]=0;
    res[0]=1;
    while ((1ll<<pnt)<=n) pnt++;
    for (ll p=pnt;p>=0;p--) {
      mul(res,res,k);
      if ((n>>p)&1) {
        for (ll i=k-1;i>=0;i--) res[i+1]=res[i];res[0]=0;
        for(int j=0;j<md.size();j++)
          res[md[j]]=(res[md[j]]-res[k]*_md[md[j]])%mod;
      }
    }
    for(int i=0;i<k;i++) ans=(ans+res[i]*b[i])%mod;
    if (ans<0) ans+=mod;
    return ans;
  }
  vector<ll> init(vector<ll> s) {
    vector<ll> coe(1,1),base(1,1);
    int len=0,m=1,b=1;
    for(int n=0;n<s.size();n++) {
      ll d=0;
      for(int i=0;i<len+1;i++) d=(d+(ll)coe[i]*s[n-i])%mod;
      if (d==0) ++m;
      else if (2*len<=n) {
        vector<ll> tmp=coe;
        ll c=mod-d*inv(b)%mod;
        while (coe.size()<base.size()+m) coe.push_back(0);
        for(int i=0;i<base.size();i++) coe[i+m]=(coe[i+m]+c*base[i])%mod;
        len=n+1-len; base=tmp; b=d; m=1;
      } else {
        ll c=mod-d*inv(b)%mod;
        while (coe.size()<base.size()+m) coe.push_back(0);
        for(int i=0;i<base.size();i++) coe[i+m]=(coe[i+m]+c*base[i])%mod;
        ++m;
      }
    }
    return coe;
  }
  vector<ll> c,a;
  void inita(vector<ll> _a){
    a=_a;
    c=init(a);c.erase(c.begin());
    for(auto &i:c) i=(mod-i)%mod;
  }
  int get(ll n) {
    return solve(n,c,vector<ll>(a.begin(),a.begin()+c.size()));
  }
  int get(vector<ll> a,ll n) {
    vector<ll> c=init(a);
    c.erase(c.begin());
    for(int i=0;i<c.size();i++) c[i]=(mod-c[i])%mod;
    return solve(n,c,vector<ll>(a.begin(),a.begin()+c.size()));
  }
};

