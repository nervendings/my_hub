//@最小生成树prim算法@
int head[30],next[200],point[200],val[200],size,dist[30];
bool vis[30];
void add (int a,int b, int v){
  int i;
  for(i=head[a];~i;i=next[i]){
    if(point[i]==b){
      if(val[i]>v)val[i]=v;
      return;
    }
  }
  point[size]=b;
  val[size]=v;
  next[size]=head[a];
  head[a]=size++;
}
struct cmp{
  bool operator()(pii a,pii b){
    return a.first>b.first;
  }
};
void prim(int s){
  int i,ans=0;
  memset(dist,-1,sizeof(dist));
  memset(vis,0,sizeof(vis));
  priority_queue<pii,vector<pii>,cmp>q;
  for (i=head[s];~i;i=next[i]){
    dist[point[i]]=val[i];
    q.push(make_pair(dist[point[i]],point[i]));
  }
  dist[s]=0;
  vis[s]=1;
  while(!q.empty()){
    pii u=q.top();
    q.pop();
    if(vis[u.second])continue;
    vis[u.second]=1;
    ans+=u.first;
    for(i=head[u.second];~i;i=next[i]){
      int j=point[i];
      if(!vis[j]&&(dist[j]>val[i]||dist[j]==-1)){
        dist[j]=val[i];
        q.push(make_pair(dist[j],j));
      }
    }
  }
  printf("%d\n",ans);
}
