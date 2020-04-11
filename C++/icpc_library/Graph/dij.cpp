namespace dij{
  struct road{
    int now;ll dis;
    road(int a=0,ll _dis=0):now(a),dis(_dis){}
    bool operator<(const road &x)const {return dis>x.dis};
  }
  ll dis[maxn];
  bool vis[maxn];
  priority_queue<road>que;
  void cal(int st,int n=maxn-5){
    fill_n(dis,n+1,1e18);fill_n(vis,n+1,0);
    que.emplace(st,0);dis[st]=0;
    while(!que.empty()){
      road t=que.top();que.pop();
      for(auto e:g[t.now]){
        ll cost=t.dis+e.cost;
        if(cost<dis[e.to]){
          dis[e.to]=cost;
          que.emplace(e.to,cost);
        }
      }
    }
  }
}
template<typename T> class shortpath{public:
  T dis[maxn];
  bool vis[maxn];
  #define pdi pair<T,int>
  priority_queue<pdi,vector<pdi>,greater<pdi> >que;
  void cal(int st,int n,vector<pdi> g[]){
    fill_n(dis,n+1,INF);fill_n(vis,n+1,0);
    que.emplace(0,st);dis[st]=0;
    while(!que.empty()){
      pdi t=que.top();que.pop();
      for(auto e:g[t.se]){
        T cost=t.fi+e.fi;
        if(cost<dis[e.se]){
          dis[e.se]=cost;
          que.emplace(cost,e.se);
        }
      }
    }
  }
};
