template<typename T>class mxf{public:
  struct node{int to,next;T cap;}e[maxm<<1];
  int cur[maxn],head[maxn],dis[maxn],gap[maxn];
  int nume=1,s,t,tot;
  void init(int n){
    rep(i,0,n) head[i]=gap[i]=dis[i]=0;
    nume=1;
  }
  void add(int a,int b,T c){
    e[++nume]={b,head[a],c};head[a]=nume;
    e[++nume]={a,head[b],0};head[b]=nume;
  }
  T dfs(int now,T flow=INF){
    if (now==t||!flow) return flow; 
    T use=0,tmp;
    int d=dis[now]-1,to;
    for (int &i=cur[now];i;i=e[i].next) {
      if(dis[to=e[i].to]==d&&(tmp=e[i].cap)){
        e[i].cap-=(tmp=dfs(to,min(flow-use,tmp)));
        e[i^1].cap+=tmp;
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
};
mxf<int> net;
