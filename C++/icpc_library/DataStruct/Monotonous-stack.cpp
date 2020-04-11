int main() {//hdu1506
  cin>>n;
  rep(i,1,n) cin>>a[i];
  ll ans=a[1];
  while(!stk.empty()) stk.pop();
  rep(i,1,n){
    while(!stk.empty()&&a[stk.top()]>=a[i]) stk.pop();
    if(!stk.empty()) l[i]=stk.top()+1;
    else l[i]=1;
    stk.push(i);
  }
  while(!stk.empty()) stk.pop();
  per(i,1,n){
    while(!stk.empty()&&a[stk.top()]>=a[i]) stk.pop();
    if(!stk.empty()) r[i]=stk.top()-1;
    else r[i]=n;
    stk.push(i);
  }
  rep(i,1,n) ans=max(ans,a[i]*(r[i]-l[i]+1));
  cout<<ans<<endl;
}
