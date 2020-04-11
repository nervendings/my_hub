const int maxn=1e5+10,maxm=sqrt(maxn+1)+10;
class sqblock{public:
  int id[maxn],sz,cnt;
  struct block{int l,r;ll sum,tag;}node[maxm];
  void init(int n){
    sz=sqrt(n+0.5);
    rep(i,1,n) id[i]=(i-1)/sz+1;cnt=id[n];
    rep(i,1,cnt) node[i].l=(i-1)*sz+1;
    rep(i,1,cnt-1) node[i].r=i*sz;node[cnt].r=n;
    rep(i,1,n) node[id[i]].sum+=arr[i];
  }
  void update(int s,int t,ll x){
    int p1=id[s],p2=id[t];
    if(p1==p2)rep(i,s,t)node[p1].sum+=x,arr[i]+=x;
    else {
      rep(i,s,node[p1].r) arr[i]+=x,node[p1].sum+=x;
      rep(i,node[p2].l,t) arr[i]+=x,node[p2].sum+=x;
      rep(i,p1+1,p2-1) node[i].tag+=x;
    }
  }
  ll query(int s,int t){
    int p1=id[s],p2=id[t];ll ans=0;
    if(p1==p2) rep(i,s,t) ans+=arr[i]+node[p1].tag;
    else {      
      rep(i,s,node[p1].r) ans+=arr[i]+node[p1].tag;
      rep(i,node[p2].l,t) ans+=arr[i]+node[p2].tag;
      rep(i,p1+1,p2-1) ans+=node[i].sum+node[i].tag*sz;
    }
    return ans;
  }
}square;
