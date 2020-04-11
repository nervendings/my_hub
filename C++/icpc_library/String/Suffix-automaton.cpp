const int maxn=1e5+10,maxsz=26+1,ch0='a';
class saffixam {public:
  int fa[maxn<<1],son[maxn<<1][maxsz];
  int last,cnt,len[maxn<<1];
  void insert(int ch) {
    int pre=last,now=++cnt;
    last=now,len[now]=len[pre]+1;
    for(; pre&&!son[pre][ch]; pre=fa[pre])son[pre][ch]=now;
    if(!pre)fa[now]=1;
    else {
      int q=son[pre][ch];
      if(len[pre]+1==len[q])fa[now]=q;
      else {
        int nq=++cnt;
        memcpy(son[nq],son[q],sizeof(son[0]));
        fa[nq]=fa[q];
        len[nq]=len[pre]+1;
        fa[q]=fa[now]=nq;
        for(; son[pre][ch]==q; pre=fa[pre])son[pre][ch]=nq;
      }
    }
  }
  void init() {
    rep(i,0,cnt) {
      memset(son[i],0,sizeof son[0]);
      fa[i]=len[i]=0;
    }
    last=cnt=1;
  }
  void insert(string &s ) {for(auto i:s)insert(i-ch0);}
  bool find(string &s) {
    int now=1;
    for(auto i:s) if(!(now=son[now][i-ch0]))return 0;
    return 1;
  }
} sam;
