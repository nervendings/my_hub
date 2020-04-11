int root;
class domtree{public://@dom为最终的支配树,root为根,cnt为每个点的支配点的数量@
  int dfn[maxn],rev[maxn],anc[maxn];
  int semi[maxn],idom[maxn];
  int fa[maxn],mi[maxn],clo;
  struct node{int to,next;};
  struct graph{
    node e[maxn];int head[maxn],nume;
    void init(int n=maxn-5){nume=0;fill_n(head,n+1,0);}
    void add(int a,int b){e[++nume]={b,head[a]};head[a]=nume;}
  }inv,nxt,dom;
  void  init(int n=maxn-5){
    clo=0;
    rep(i,1,n)fa[i]=mi[i]=semi[i]=i,rev[i]=dfn[i]=anc[i]=idom[i]=0;
    nxt.init(n),inv.init(n),dom.init(n);
  }
  void add(int a,int b){inv.add(b,a),nxt.add(a,b);}
  int find(int now){
    if(fa[now]==now) return now;
    int fx=fa[now],y=find(fa[now]);
    if(dfn[semi[mi[fx]]]<dfn[semi[mi[now]]])
      mi[now]=mi[fx];
    return fa[now]=y;
  }
  void tdfs(int now){
    dfn[now]=++clo;rev[clo]=now;
    forn(i,now,nxt.head,nxt.e)if(!dfn[nxt.e[i].to])
      anc[nxt.e[i].to]=now,tdfs(nxt.e[i].to);
  }
  void maketree(int root,int n=maxn-5){
    tdfs(root);
    per(i,2,n){
      int now=rev[i],tmp=n;
      forn(i,now,inv.head,inv.e){
        int to=inv.e[i].to;if(!dfn[to]) continue;
        if(dfn[to]<dfn[now]) tmp=min(tmp,dfn[to]);
        else find(to),tmp=min(tmp,dfn[semi[mi[to]]]);
      }
      semi[now]=rev[tmp];fa[now]=anc[now];
      dom.add(semi[now],now);
      now=rev[i-1];
      forn(i,now,dom.head,dom.e){
        int to=dom.e[i].to;find(to);
        if(semi[mi[to]]==now) idom[to]=now;
        else idom[to]=mi[to];
      }
    }
    rep(i,2,n){
      int to=rev[i];
      if(idom[to]!=semi[to]) idom[to]=idom[idom[to]];
    }
    dom.init(n);
    rep(i,1,n) if(i!=root)dom.add(idom[i],i);
  }
}tree;
