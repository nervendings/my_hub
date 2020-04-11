//@rmq求lca+快速求树上链交@
const int maxp=18;
class graph{public:
  struct node{int to,next;}e[maxn<<1];
  int head[maxn],nume,dfn[maxn],deep[maxn];
  int logn[maxn],pos[maxp][maxn],cnt;
  inline void add(int a,int b){e[++nume]={b,head[a]};head[a]=nume;}
  void init(int n){rep(i,1,n) head[i]=0;cnt=0,nume=1;}
  void cal(int n){
    logn[2]=1;
    rep(i,3,n) logn[i]=logn[i>>1]+1;
    for(int j=1;(1<<j)<=n;j++) for(int i=1;i+(1<<j)-1<=n;++i){
      int r=i+(1<<(j-1));
      if(deep[pos[j-1][i]]<deep[pos[j-1][r]]) pos[j][i]=pos[j-1][i];
      else pos[j][i]=pos[j-1][r];
    }
  }
  void dfs(int now=root,int fa=root,int d=1){
    dfn[now]=++cnt;deep[now]=d;pos[0][cnt]=now;
    forn(i,now){
      if(e[i].to==fa) continue;
      dfs(e[i].to,now,d+1);pos[0][++cnt]=now;
    }
  }
  inline int lca(int l,int r){
    l=dfn[l],r=dfn[r];if(l>r) swap(l,r);
    int lg=logn[r-l+1];
    if(deep[pos[lg][l]]<deep[pos[lg][r-(1<<lg)+1]])return pos[lg][l];
    else return pos[lg][r-(1<<lg)+1];
  }
  inline int getdis(int a,int b){return deep[a]+deep[b]-2*deep[lca(a,b)];}
  void getlca(){dfs();cal(cnt);}
  inline bool check(int a,int b){return lca(a,b)==a;}
  int getans(int a1,int a2,int b1,int b2){
    int ra=lca(a1,a2);
    bool f1=check(ra,b1),f2=check(ra,b2);
    if(!f1&&!f2) return 0;
    if(f1&&f2){
      int rb=lca(b1,b2);
      if(!( check(rb,a1)||check(rb,a2)))return 0;
      int r1=lca(a1,b1),r2=lca(a1,b2);
      int r3=lca(a2,b1),r4=lca(a2,b2);
      if(r1==r3&&r2==r4) return 1;
      return getdis(r1==ra?r3:r1,r2==ra?r4:r2)+1;
    }
    if(!f1)swap(b1,b2);
    int r1=lca(a1,b1),r3=lca(a2,b1);
    return getdis(r1==ra?r3:r1,ra)+1;
  }
}g;
