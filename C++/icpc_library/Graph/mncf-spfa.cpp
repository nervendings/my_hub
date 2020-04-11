//@zkw费用流,单路增广@
//@可将单路增广改为多路增广+当前弧优化,但提升不大@
template<typename T1,typename T2>class mcf{public:
  int nume=1,s,t,numv,head[maxn],pre[maxn];
  bool vis[maxn];
  queue<int>q;
  T1 flow[maxn],mflow;
  T2 dis[maxn],mcost;
  struct node{int to,next;T1 cap;T2 cost;}e[maxm<<1];
  void init(int n=maxn-10){
    numv=n;
    fill(head,head+n+2,0);nume=1,mflow=mcost=0;
  }
  inline void add(int from,int to,int cap,T2 cost){
    e[++nume]={to,head[from],cap,cost};head[from]=nume;
    e[++nume]={from,head[to],0,-cost};head[to]=nume;
  }
  bool spfa(){
    fill(dis,dis+2+numv,INF);
    fill(vis,vis+2+numv,false);
    dis[s]=0;flow[s]=INF;q.push(s);
    while (!q.empty()){
      int now=q.front();q.pop();
      vis[now]=false;
      for (int i=head[now];i;i=e[i].next){
        int to=e[i].to;
        T2 cost=e[i].cost;
        if (e[i].cap&&dis[now]+cost<dis[to]){
          dis[to]=dis[now]+cost;
          flow[to]=min(flow[now],e[i].cap);
          pre[to]=i;
          if (!vis[to]){
            vis[to]=true;
            q.push(to);
          }
        }
      }
    }
    return dis[t]<INF;
  }
  void dfs(){
    int x=t;
    while (x!=s){
      int i=pre[x];
      e[i].cap-=flow[t];
      e[i^1].cap+=flow[t];
      x=e[i^1].to;
    }
    mflow+=flow[t];
    mcost+=(T2)flow[t]*dis[t];
  }
  pair<T1,T2> getcost(int ss,int tt){
    s=ss,t=tt;
    while (spfa())dfs();
    return make_pair(mflow,mcost);
  }
};
mcf<int,int>net;
