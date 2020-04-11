struct PAT {
  struct node {
    int len,num,fail,son[26];
  } t[maxn];
  int last,n,tot,s[maxn];
  void init() {
    memset(t,0,sizeof(t));
    tot=last=1;
    n=0;
    t[0].len=0;
    t[1].len=-1;
    t[0].fail=t[1].fail=1;
    s[0]=-1;
  }
  int add(int c) {
    int p=last;
    s[++n]=c;
    while(s[n]!=s[n-1-t[p].len])
      p=t[p].fail;
    if(!t[p].son[c]) {
      int v=++tot,k=t[p].fail;
      while(s[n]!=s[n-t[k].len-1])
        k=t[k].fail;
      t[v].fail=t[k].son[c];
      t[v].len=t[p].len+2;
      t[v].num=t[t[v].fail].num+1;
      t[p].son[c]=v;
    }
    last=t[p].son[c];
    return t[last].num;
  }
} T;
