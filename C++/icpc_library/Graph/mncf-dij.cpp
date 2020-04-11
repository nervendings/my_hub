//@原始对偶算法,dijkstra寻找增广路,单路增广@
//@无优化空间@
template<typename T1,typename T2,const int N>class mcf{public:
#define pdi pair<T2,int>
  priority_queue<pdi,vector<pdi>,greater<pdi>>que;
  struct node{int to;T1 cap;T2 cost;int rev;};
  int prev[N+10],pree[N+10],numv;
  T2 dis[N+10],h[N+10];
  vector<node> g[N+10];
  void init(int n){
    numv=n;
    rep(i,0,n) g[i].clear();
  }
  inline void add(int from,int to,T1 cap,T2 cost){
    g[from].push_back({to,cap,cost,(int)g[to].size()});
    g[to].push_back({from,0,-cost,(int)g[from].size()-1});
  }
  pair<T1,T2>getcost(int s,int t,int n){
    numv=n;
    T1 flow=0; T2 cost=0;
    fill_n(h,numv+1,0);
    while(1){
      fill_n(dis,numv+1,INF);
      dis[s]=0;que.push(make_pair(0,s));
      while(!que.empty()){
        auto now=que.top();que.pop();
        if(dis[now.second]<now.first)continue;
        int x=now.second;
        int cnt=0;
        for(auto &i:g[x])
          if(i.cap>0&&dis[i.to]>dis[x]+h[x]-h[i.to]+i.cost){
            dis[i.to]=dis[x]+i.cost+h[x]-h[i.to];
            prev[i.to]=x;
            pree[i.to]=cnt++;
            que.push(make_pair(dis[i.to],i.to));
          }else cnt++;
      }
      if(dis[t]==INF)break;
      rep(i,0,numv) h[i]+=dis[i];
      T1 d=INF;
      for(int now=t;now!=s;now=prev[now])
        d=min(d,g[prev[now]][pree[now]].cap);
      if(d==INF)break;
      flow+=d;cost+=d*h[t];
      for(int now=t;now!=s;now=prev[now]){
        node &e=g[prev[now]][pree[now]];
        e.cap-=d,g[now][e.rev].cap+=d;
      }
    }
    return make_pair(flow,cost);
  }
};
mcf<int,int,(int)1e4>net;
