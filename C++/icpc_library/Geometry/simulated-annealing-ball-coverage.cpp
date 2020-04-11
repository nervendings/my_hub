double cx=0,cy=0,cz=0;
double x[maxn],y[maxn],z[maxn];
double dis(int now){
  return sqrt((x[now]-cx)*(x[now]-cx)+
        (y[now]-cy)*(y[now]-cy)+
        (z[now]-cz)*(z[now]-cz));
}
int main() {
  cin>>n;
  rep(i,1,n) cin>>x[i]>>y[i]>>z[i];
  int pos=1;
  double dmax=1e4,ans=1e18;
  while(dmax>1e-7){
    rep(i,1,n) if(dis(i)>dis(pos)) pos=i;
    double d=dis(pos);
    ans=min(ans,d);
    cx+=(x[pos]-cx)/d*dmax;
    cy+=(y[pos]-cy)/d*dmax;
    cz+=(z[pos]-cz)/d*dmax;
    dmax*=0.98;
  }
  printf("%.6f\n",ans);
  return 0;
}
