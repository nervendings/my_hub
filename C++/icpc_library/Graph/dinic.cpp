template<typename T>class mxf{public:
  struct node{int to,next;T cap;}e[maxm<<1];
  int cur[maxn],head[maxn],que[maxn],dis[maxn];
  int nume=1,s,t,tot,tp,ed;
  inline void adde(int a,int b,T c){e[++nume]={b,head[a],c};head[a]=nume;}
  inline void add(int a,int b,T c){adde(a,b,c);adde(b,a,0);}
  void init(int n=maxn-1){memset(head,0,(n+1)<<2);nume=1;}
  bool bfs(){
    rep(i,0,ed) dis[que[i]]=0;
    dis[t]=1,que[0]=t;
    tp=0,ed=1;
    cur[t]=head[t];
    int now,to;
    while(tp!=ed) for(int i=head[now=que[tp++]];i;i=e[i].next)
      if(dis[to=e[i].to]==0&&e[i^1].cap>0){
        cur[to]=head[to];
        dis[to]=dis[now]+1;
        if((que[ed++]=to)==s) return true;
      }
    return false;
  }
  T dfs(int now,T flow=INF){
    if(now==t||flow==0) return flow;
    int to,d=dis[now]-1;
    T use=0,tmp;
    for(int &i=cur[now];i;i=e[i].next){
      if(dis[to=e[i].to]!=d||!(tmp=e[i].cap))continue;
      e[i].cap-=(tmp=dfs(to,min(tmp,flow-use)));
      e[i^1].cap+=tmp,use+=tmp;
      if(use==flow) return use;
    }
    if(use==0) dis[now]=-1;
    return use;
  }
  T getflow(int ss,int tt,int n,T ans=0){
    s=ss,t=tt,tot=n;
    while(bfs())ans+=dfs(s);
    return ans;
  }
};
mxf<int> net;
