const double eps=1e-8;
template<typename T>class mxf{public:
  struct node{int to,next;T cap;}e[maxm<<1];
  int cur[maxn],head[maxn],que[maxn],dis[maxn],nume=1,s,t;
  inline void adde(int a,int b,T c){
    e[++nume]={b,head[a],c};head[a]=nume;
  }
  inline void add(int a,int b,T c){adde(a,b,c);adde(b,a,0);}
  void init(int n=maxn-1){memset(head,0,(n+1)<<2);nume=1;}
  bool bfs(){
    memset(dis,-1,(t+1)<<2);
    dis[t]=0,que[0]=t;
    int tp=0,ed=1;
    while(tp!=ed){
      int now=que[tp++];if(tp==maxn) tp=0;
      for(int i=head[now];i;i=e[i].next){
        int to=e[i].to;
        if(dis[to]==-1&&e[i^1].cap>0){
          dis[to]=dis[now]+1;
          if(to==s) return true;
          que[ed++]=to;
          if(ed==maxn) ed=0;
        }
      }
    }
    return false;
  }
  T dfs(int now,T flow=1e9){
    if(now==t||flow==0) return flow;
    T use=0;
    for(int &i=head[now];i&&use!=flow;i=e[i].next){
      int to=e[i].to;
      if(dis[to]+1!=dis[now])continue;
      T tmp=dfs(to,min(e[i].cap,flow-use));
      e[i].cap-=tmp,e[i^1].cap+=tmp,use+=tmp;
    }
    if(use==0) dis[now]=-1;
    return use;
  }
  T getflow(int ss,int tt){
    s=ss,t=tt;T ans=0;
    memcpy(cur,head,(t+1)<<2);
    while(bfs()){
      ans+=dfs(s);
      memcpy(head,cur,(t+1)<<2);
    }
    return ans;
  }
};
mxf<double> net;
const int maxn2=500;
int mt[maxn2][maxn2];
double d[maxn2];
int val[maxn2],tag[maxn2];
void init(int n){rep(i,1,n)rep(j,i+1,n) mt[i][j]=mt[j][i]=0;}
void adde(int a,int b,int v){mt[a][b]=mt[b][a]=v;}
const double all=400*2200;//@点权和+边权和*2@
bool check(double mid){
  int s=n+1,t=n+2;
  net.init(n+3);
  double f=0;
  rep(i,1,n){
    d[i]=0.0;
    rep(j,1,n){
      if(i==j||!mt[i][j])continue;
      d[i]+=mt[i][j];
//@如果公式计算出来,边权跟mid有关,就要加上相应的mid@
      net.add(i,j,mt[i][j]);
    }
  }
  rep(i,1,n){
    if(tag[i]){
      f+=all+2*mid-d[i];
      net.add(s,i,INF);
    }else {
      net.add(s,i,all);
      net.add(i,t,all+2*mid-d[i]);
//@有点权的话，这个2*mid还要再乘那个点权@
    }
  }
  double x=net.getflow(s,t);
  double ans=(all*n-f-x)*0.5;
  return ans>eps;
}
int main(){IO;
  cin>>casn;
  cout<<fixed<<setprecision(10);
  rep(kase,1,casn){
    cin>>n;
    init(n);
    rep(i,1,n)cin>>val[i];
    rep(i,1,n)rep(j,i+1,n)
      if(val[j]<val[i]) adde(i,j,1);
//    rep(i,1,n) tag[i]=0;//@是否必须用@
    double l=0,r=n,mid;
    while(r-l>=eps){
      mid=(l+r)*0.5;
      if(check(mid)) l=mid;
      else r=mid;
    }
    cout<<"Case #"<<kase<<": "<<(l+r)*0.5<<'\n';
  }
  return 0;
}
