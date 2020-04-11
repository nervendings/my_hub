double dis[maxn];
struct node{
  double x,y1,y2;int tag;
  bool operator <(node &other) const{return x<other.x;}
}seg[maxn];
class segtree{public:
#define nd  node[now]
#define ndl node[now<<1]
#define ndr node[now<<1|1]
  struct segnode {
    int l,r,tag;double dis;
    inline int mid(){return (r+l)>>1;}
    inline int len(){return r-l+1;}
  }node[maxn<<2|3];
  inline void update(int now){
    if(nd.tag) nd.dis=dis[nd.r+1]-dis[nd.l];
    else if(nd.len()==1) nd.dis=0;
    else nd.dis=ndl.dis+ndr.dis;
  }
  void maketree(int s,int t,int now=1){
    nd={s,t,0,0};
    if(s==t) return ;
    maketree(s,nd.mid(),now<<1);
    maketree(nd.mid()+1,t,now<<1|1);
  }
  void update(int s,int t,int x,int now=1){
    if(s<=nd.l&&t>=nd.r) {
    nd.tag+=x;update(now);
    return ;
    }
    if(s<=ndl.r) update(s,t,x,now<<1);
    if(t>ndl.r) update(s,t,x,now<<1|1);
    update(now);
  }
}tree;
int main() {IO;cout<<fixed<<setprecision(2);
  while((cin>>n)&&n){
  m=0;
  rep(i,1,n){
    double a,b,c,d;cin>>a>>b>>c>>d;
    dis[++m]=b;seg[m]={a,b,d,1};
    dis[++m]=d;seg[m]={c,b,d,-1};
  }
  sort(dis+1,dis+m+1);
  sort(seg+1,seg+m+1);
  int cnt=unique(dis+1,dis+1+m)-dis-1;
  tree.maketree(1,cnt);
  double ans=0;
  rep(i,1,m-1){
    int l=lower_bound(dis+1,dis+1+cnt,seg[i].y1)-dis;
    int r=lower_bound(dis+1,dis+1+cnt,seg[i].y2)-dis;
    r--;
    if(l<=r) tree.update(l,r,seg[i].tag);
    ans+=tree.node[1].dis*(seg[i+1].x-seg[i].x);
  }
  cout<<"Test case #"<<++casn<<endl;
  cout<<"Total explored area: "<<ans<<endl<<endl;
  }
}
