#include<bits/stdc++.h>
#define rep(ii,a,b) for(int ii=a;ii<=b;++ii)
#define all(x) x.begin(),x.end()
using namespace std;//head
const int maxn=2e5+10,maxm=2e6+10;
int casn,n,m,k;
int rt[maxn];//@树根@
class ptree{public:
#define nd node[now]
#define ndp node[pre]
#define mid (s+t)/2
  int cnt;
  struct segnode{int l,r,sum;}node[maxn*20];
  void init(){cnt=0;}
  void update(int pre,int &now,int pos,int s=1,int t=k){
    now=++cnt;nd=ndp;nd.sum++;
    if(s==t) return ;
    if(pos<=mid) update(ndp.l,nd.l,pos,s,mid);
    else update(ndp.r,nd.r,pos,mid+1,t);
  }
  int query(int pre,int now,int pos,int s=1,int t=k){
    if(s==t) return s;
    int sum=node[nd.l].sum-node[ndp.l].sum;
    if(pos<=sum) return query(ndp.l,nd.l,pos,s,mid);
    else return query(ndp.r,nd.r,pos-sum,mid+1,t);
  }
#undef mid
}tree;
int a[maxn];
vector<int>pos;
int main() {IO;
  cin>>n>>m;
  rep(i,1,n) cin>>a[i];
  rep(i,1,n) pos.push_back(a[i]);
  sort(all(pos));
  pos.erase(unique(all(pos)),pos.end());
  k=pos.size();
  rep(i,1,n){
    int id=lower_bound(all(pos),a[i])-pos.begin();
    tree.update(rt[i-1],rt[i],id+1);
  }
  while(m--){
    int a,b,c;cin>>a>>b>>c;
    cout<<pos[tree.query(rt[a-1],rt[b],c)-1]<<'\n';
  }
  return 0;
}
