ll a[maxn],ans[maxn],sz,sum;
class block{public:
  ll cnt[maxn];
  struct node{ll l,r,id;
    bool operator <(const node &b)const {
      if(l/sz!=b.l/sz) return l<b.l;
      if((l/sz)&1) return r<b.r;
      return r>b.r;
    }
  };
  void update(int pos,ll flag=1){
    sum+=flag*a[pos]*(cnt[a[pos]]*2ll+flag);
    cnt[a[pos]]+=flag;
  }
}ask;
vector<block::node> tab;
int main() {
  cin>>n>>m;sz=sqrt(n);
  rep(i,1,n) cin>>a[i];
  rep(i,1,m) {
    int a,b;cin>>a>>b;
    tab.push_back({a,b,i});
  }
  sort(all(tab));
  int l=tab[0].l,r=tab[0].l-1;
  for(auto now:tab){
    while(l>now.l) ask.update(--l,1);
    while(l<now.l) ask.update(l++,-1);
    while(r<now.r) ask.update(++r,1);
    while(r>now.r) ask.update(r--,-1);
    ans[now.id]=sum;
  }
}
