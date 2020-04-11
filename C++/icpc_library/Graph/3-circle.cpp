vector<pii>g[maxn];
int deg[maxn],a[maxn],b[maxn],cnt[maxn],pos[maxn],v[maxn];
int main() {
  while(cin>>n>>m){
    rep(i,1,n){
      g[i].clear();
      v[i]=deg[i]=pos[i]=0;
    }
    rep(i,1,m){
      cin>>a[i]>>b[i];
      deg[a[i]]++,deg[b[i]]++;
    }
    rep(i,1,m){
      cnt[i]=0;
      if(deg[a[i]]<deg[b[i]])g[a[i]].emplace_back(b[i],i);
      else if(deg[a[i]]>deg[b[i]])g[b[i]].emplace_back(a[i],i);
      else {
        if(a[i]<b[i]) g[a[i]].emplace_back(b[i],i);
        else g[b[i]].emplace_back(a[i],i);
      }
    }
    rep(i,1,m){
      int u=a[i],to=b[i];
      for(auto j:g[u]) pos[j.fi]=j.se,v[j.fi]=i+1;
      for(auto j:g[to]){
        int t=j.fi;
        if(v[t]==i+1){
          cnt[i]++;
          cnt[pos[t]]++;
          cnt[j.se]++;
        }
      }
    }
    ll ans=0;
    rep(i,1,m) ans+=1ll*cnt[i]*(cnt[i]-1)/2;
    cout<<ans<<endl;
  }
}
