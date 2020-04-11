int root;
const ll rangel=0,ranger=1e9+10;
class dsegtree{public:
#define nd node[now]
#define ndl node[node[now].son[0]]
#define ndr node[node[now].son[1]]
	struct dsegnode{
		int son[2],mx,tag;
		void update(int x){mx+=x,tag+=x;}
	}node[maxn*50];
	int cnt;
	void pushup(int now){nd.mx=max(ndl.mx,ndr.mx);}
	void pushdown(int now){
		if(nd.tag){
			if(!nd.son[0]) nd.son[0]=++cnt;
			if(!nd.son[1]) nd.son[1]=++cnt;
			ndl.update(nd.tag),ndr.update(nd.tag);
			nd.tag=0;
		}
	}
	void update(ll s,ll t,int x,ll l=rangel,ll r=ranger,int &now=root){
		if(!now) {now=++cnt;nd={0,0,0,0};}
		if(s<=l&&t>=r){
			nd.update(x);
			return ;
		}
		pushdown(now);
		if(s<=((l+r)>>1)) update(s,t,x,l,(l+r)>>1,nd.son[0]);
		if(t>((l+r)>>1)) update(s,t,x,1+((l+r)>>1),r,nd.son[1]);
		pushup(now);
	}
}tree;
