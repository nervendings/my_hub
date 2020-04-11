int vis[maxn];
int cnt;
struct node {
  int to,flag,id,next;
}e[maxm];
int head[maxn],nume,deg[maxn];
inline void _add(int a,int b,int c){
  e[++nume]=(node){b,1,c,head[a]};
  head[a]=nume;
}
inline void add(int a,int b,int c){
  _add(a,b,c);_add(b,a,-c);
}
vector<int> ans[maxn];
void dfs(int now){
  vis[now]=1;
  for(int i=head[now];i;i=e[i].next){
    if(!e[i].flag) continue;
    e[i].flag=e[i^1].flag=0;
    dfs(e[i].to);
    ans[cnt].push_backe(-e[i].id);
  }
}
void solve(){
  rep(i,1,n){
    if(!vis[i]&&deg[i]&1) {
      cnt++;
      dfs(i);
    }
  }
  rep(i,1,n){
    if(!vis[i]&&deg[i]){
      cnt++;
      dfs(i);
    }
  }
}
