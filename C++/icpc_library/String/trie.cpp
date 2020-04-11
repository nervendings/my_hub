const int csize=26,minc='a';
class trie{public:
#define nd node[now]
	struct tnode{
		int cnt,son[csize];
		tnode(){
			cnt=0;
			memset(son,0,sizeof son);
		}
	}node[maxn];
  int sz=0;
  void insert(char *s,int len){
    int now=0;
    rep(i,0,len-1){
      int ch=s[i]-minc;
      if(!nd.son[ch]) nd.son[ch]=++sz;
      now=nd.son[ch];
    }
    node[now].cnt++;
  }
  int find(char *s,int len){
    int ch,now=0;
    rep(i,0,len-1){
      ch=s[i]-minc;
      if(!nd.son[ch]) return -1;
      now=nd.son[ch];
    }
    if(!nd.cnt) return -1;
    return 1;
  }
}tree;
