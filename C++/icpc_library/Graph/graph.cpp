class graph{public:
  struct node{int to,next,cost;};
  node e[maxm];int head[maxn],nume;
  void init(int n=maxn-5){nume=0;fill_n(head,n+1,0);}
  void add(int a,int b,int c){e[++nume]={b,head[a],c};head[a]=nume;}
}
