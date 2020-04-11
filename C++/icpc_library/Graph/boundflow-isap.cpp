//@上下界可行流@
template<typename T>class mxf{public:
  struct node{int id,to,rev;T cap;}w[maxm<<1],e[maxm<<1];
  int cur[maxn],head[maxn],dis[maxn],gap[maxn];
  T up[maxm<<1],in[maxn],sum,ans[maxm<<1];
  int num[maxn],numv,nume,s,t,tot,tp,ed,fr[maxm<<1];
  T dfs(int now,T flow=0x3f3f3f3f){
    if (now==t||!flow) return flow; 
    T use=0,tmp;
    int d=dis[now]-1,to;
    for (int &i=cur[now];i<=num[now];++i) {
      if(dis[to=e[i].to]==d&&(tmp=e[i].cap)){
        e[i].cap-=(tmp=dfs(to,min(flow-use,tmp)));
        e[e[i].rev].cap+=tmp;
        if((use+=tmp)==flow) return use;
      }
    }
    if (!--gap[dis[now]]) dis[s]=tot+1; 
    ++gap[++dis[now]];
    cur[now]=head[now];
    return use;
  }
  T getflow(int ss,int tt,int n,T ans=0){
    tot=n;s=ss;t=tt;gap[0]=tot;
    memcpy(cur,head,(tot+1)<<2);
    while(dis[s]<=tot) ans+=dfs(s);
    return ans;
  }
  void init(int n){
    rep(i,0,n) num[i]=in[i]=head[i]=dis[i]=0;
    nume=0;tot=n;sum=0;
  }
  void add(int a,int b,T c,int id){
    w[++nume]=(node){id,b,0,c};++num[a],fr[nume]=a;
    w[++nume]=(node){0,a,0,0}; ++num[b],fr[nume]=b;
  }
  void addbound(int a,int b,T c,T d,int id){
    add(a,b,d-c,id);
    up[id]=d,in[b]+=c,in[a]-=c;    
  }
  bool fesbflow(int n){
    s=n+1,t=n+2;numv=n;tot=t;
    rep(i,1,numv){
      if(in[i]>0) add(s,i,in[i],0),sum+=in[i];
      if(in[i]<0) add(i,t,-in[i],0);
    }
    head[1]=1;
    rep(i,2,tot) head[i]=head[i-1]+num[i-1];
    rep(i,1,tot-1) num[i]=head[i+1]-1;
    num[tot]=nume;
    rep(i,1,nume){
      e[head[fr[i]]+cur[fr[i]]++]=w[i];
      if(!(i%2)){
        e[head[fr[i]]+cur[fr[i]]-1].rev=head[w[i].to]+cur[w[i].to]-1;
        e[head[w[i].to]+cur[w[i].to]-1].rev=head[fr[i]]+cur[fr[i]]-1;
      }
    }
    T flow=getflow(s,t,t);
    if(flow<sum) return 0;
    rep(i,1,nume){
      node &x=e[i];
      if(x.id) ans[x.id]=up[x.id]-x.cap;
    }
    return 1;
  }
};
mxf<int> net;
