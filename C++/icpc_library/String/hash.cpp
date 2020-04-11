const ll decm=13331,modh=(ll)1e17+13;
inline ll mulh(ll a,ll b){
	ll tmp=(a*b-(ll)((long double)a/modh*b+1.0e-8)*modh);
	return tmp<0?tmp+modh:tmp;
}
inline ll addh(ll a,ll b){ll x=a+b;if(x<0)return a+b+modh;else if(x>=modh)x-modh;else return x;}
ll pw[maxn];
void init(int n=maxn-5){pw[0]=1;rep(i,1,n) pw[i]=mulh(pw[i-1],decm);
class strhash{public:
  ll hs[maxn],len;
  void calhs(string &s,int n){len=n;rep(i,0,len-1)hs[i+1]=addh(mulh(hs[i],decm),s[i]);}
  inline ll geths(int a,int b){return addh(hs[b],-mulh(hs[a-1],pw[b-a+1]));}
}table;
