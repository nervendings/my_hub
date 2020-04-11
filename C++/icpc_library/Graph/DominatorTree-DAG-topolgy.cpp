int cntin[maxn];
struct node{int to,next;};
class graph{public:
  node e[maxn];int head[maxn],nume;
  void init(int n=maxn-5){nume=0;fill_n(head,n+1,0);}
  void add(int a,int b){e[++nume]={b,head[a]};head[a]=nume;}
}inv,nxt,dom;
class domtree{public://@DAG@
  int deep[maxn],anc[maxn][maxp],que[maxn];
  vector<int>edge;
  void init(int n=maxn-5){
    inv.init(n),nxt.init(n),dom.init(n);
    edge.clear();
  }
  void bit(int &x,int h){
    for(int i=0;h>0;++i){
      if(h&1) x=anc[x][i];
      h>>=1;
    }
  }
  void add(int a,int b){nxt.add(a,b);inv.add(b,a);}
  int lca(int a,int b){
    if(deep[a]<deep[b]) swap(a,b);
    bit(a,deep[a]-deep[b]);
    if(a==b) return a;
    per(i,0,maxp-1) if(anc[a][i]!=anc[b][i])
      a=anc[a][i],b=anc[b][i];
    return anc[a][0];
  }
  void tpsort(int n){
    int tp=0,ed=0;
    rep(i,1,n) {
      if(!cntin[i]) {
        que[ed++]=i;
        inv.add(0,i);
        nxt.add(i,0);
        edge.push_back(i);
      }
    }
    while(ed!=tp){
      int now=que[tp++];
      forn(i,now,inv.head,inv.e){
        int to=inv.e[i].to;
        cntin[to]--;
        if(!cntin[to]) que[ed++]=to,edge.push_back(to);
      }
    }
  }
  void maketree(int n){
    tpsort(n);
    for(auto i:edge){
      int fa=-1;
      forn(j,i,nxt.head,nxt.e){
        int to=nxt.e[j].to;
        if(fa==-1) fa=to;
        else fa=lca(fa,to);
      }fa=fa==-1?0:fa;
      deep[i]=deep[fa]+1,anc[i][0]=fa;
      rep(j,1,maxp-1) anc[i][j]=anc[anc[i][j-1]][j-1];
      dom.add(fa,i);
    }
  }
  int ans[maxn];
  int cal(int now){
    ans[now]=1;
    forn(i,now,dom.head,dom.e) ans[now]+=cal(dom.e[i].to);
    return ans[now];
  }
}tree;
