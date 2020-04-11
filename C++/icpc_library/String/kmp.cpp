//@输入的数组从0开始,next函数为p,从1开始@
template<typename T>class prefix{public:
  int p[maxn],lens;
  T *s;
  void init(T *_s,int _lens){
    s=_s,lens=_lens;
    rep(i,0,lens-1) p[i]=0;
    p[0]=-1;
    int now=0,pos=-1;
    while(now<lens)
      if(pos==-1||s[now]==s[pos]) p[++now]=++pos;
      else pos=p[pos];
  }
  vector<int> find(T *t,int lent){
    int now,pos=0;
    vector<int> ans;
    while(now<lent) {
      if(pos==-1||t[now]==s[pos]) pos++,now++;
      else pos=p[pos];
      if(pos==lens) pos=p[pos],ans.push_back(now-lens);
    }
    return ans;
  }
};
prefix<char> kmp;
