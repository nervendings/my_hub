const int csize=128,minc=0;
class autom{public:
#define nd node[now]
  struct acnode{int id,son[csize],fail;}node[maxn];
  int sz=0;
  queue<int> que;
  void clear(int n=maxn-5){
    memset(node,0,sizeof(acnode)*n);
    sz=0;
  }
  void insert(int id,char *s,int len=0){
    if(!len)len=strlen(s);
    int now=0;
    rep(i,0,len-1){
      int ch=s[i]-minc;
      if(!nd.son[ch]) nd.son[ch]=++sz;
      now=nd.son[ch];
    }
    nd.id=id;
  }
  void init(){
    int now=0;
    rep(i,0,csize-1) if(nd.son[i])
      que.push(nd.son[i]);
    while(!que.empty()){
      now=que.front();que.pop();
      rep(i,0,csize-1){
        if(nd.son[i]) {
          node[nd.son[i]].fail=node[nd.fail].son[i];
          que.push(nd.son[i]);
        }else nd.son[i]=node[nd.fail].son[i];
      }
    }
  }
  vector<int> query(char *t,int len=0){
    if(!len)len=strlen(t);
    int now=0;
    vector<int> ans;
    rep(i,0,len-1) {
      now=nd.son[t[i]-minc];
      for(int j=now;j;j=node[j].fail)
        if(node[j].id)ans.push_back(node[j].id);
    }
    return ans;
  }
}acam;
