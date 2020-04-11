ll euler(ll n) {
  ll res=n,a=n;
  for(int i=2; i*i<=a; i++) if(a%i==0) {
    res=res/i*(i-1);
    while(a%i==0) a/=i;
  }
  if(a>1) res=res/a*(a-1);
  return res;
}
int euler[maxn];
void geteul(int n=maxn-5) {
  euler[1]=1;
  for(int i=2; i<=n; i++) euler[i]=i;
  for(int i=2; i<=n; i++)if(euler[i]==i)
    for(int j=i; j<=n; j+=i) euler[j]=euler[j]/i*(i-1);
}
