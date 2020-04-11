int pre[maxn],rk[maxn];
int find(int a){
	if(pre[a]==-1) return a;
	int t,rt=a;
	while(pre[rt]!=-1) rt=pre[rt];
	while(a!=rt)t=pre[a],pre[a]=rt,a=t;
	return rt;
}
#define same(a,b) (find(a)==find(b))
void unite(int a,int b){
	a=find(a),b=find(b);
	if(a==b) return;
	if(rk[a]>rk[b])pre[b]=a;
	else{
		pre[a]=b;
		if(rk[a]==rk[b])rk[b]++;
	}
}
class ufs{public:
  void init(int n){rep(i,0,n) pre[i]=i;}
  int find(int a){return pre[a]==a?a:pre[a]=find(pre[a]);}
  bool same(int a,int b) {return find(a)==find(b);}
  void unite(int a,int b){
    a=find(a),b=find(b);
    if(a==b) return;
    pre[b]=a;
  }
}dsu;
