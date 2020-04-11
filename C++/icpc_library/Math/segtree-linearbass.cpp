class segtree{public:
#define nd node[now]
#define ndl node[now<<1]
#define ndr node[now<<1|1]
	struct segnode{
		int l,r,flag,val;
		int d[32];
		inline void init(){val=flag=0;memset(d,0,sizeof d);}
		inline void insert(ll x){
			for(register int i=30;x&&i>=0;--i)
					if(x&(1ll<<i)){
						if(!d[i]) {d[i]=x;return;}
						else x^=d[i];
					}
		}
		int count(){int ans=0;per(i,0,30) if(d[i])ans++; return ans;}
		void update(int x){val^=x;flag^=x;}
	}node[maxn<<2|3];
	inline segnode marge(segnode &a,segnode b)const {
		segnode ans;ans.init();
		per(i,0,30) ans.insert(a.d[i]),ans.insert(b.d[i]);
		ans.insert(a.val^b.val);
		ans.val=a.val;
		ans.l=a.l,ans.r=b.r;
		return ans;
	}
	inline void down(int now){
		if(nd.flag){
			ndl.update(nd.flag);ndr.update(nd.flag);
			nd.flag=0;
		}
	}
	void maketree(int s,int t,int now=1){
		nd.l=s,nd.r=t;nd.init();
		if(s==t) {cin>>nd.val;return ;}
		maketree(s,(s+t)/2,now<<1);
		maketree((s+t)/2+1,t,now<<1|1);
		nd=marge(ndl,ndr);
	}
	void update(int s,int t,int x,int now=1){
		if(s<=nd.l&&t>=nd.r) {nd.update(x);return;}
		down(now);
		if(s<=ndl.r) update(s,t,x,now<<1);
		if(t>ndl.r) update(s,t,x,now<<1|1);
		nd=marge(ndl,ndr);
	}
	segnode query(int s,int t,int now=1){
		if(s<=nd.l&&t>=nd.r) {
			if(s==nd.l) {
				segnode x;x.init();
				return marge(x,nd);
			}else return nd;
		}
		down(now);
		segnode ans;ans.init();
		if(s<=ndl.r) ans=marge(ans,query(s,t,now<<1));
		if(t>ndl.r) ans=marge(ans,query(s,t,now<<1|1));
		nd=marge(ndl,ndr);
		return ans;
	}
}tree;
int main() {
    cin>>n>>m;
    register int a,b,c,d;
    tree.maketree(1,n);
    while(m--){
        cin>>a>>b>>c;
        if(a==1)cin>>d;tree.update(b,c,d);
        else cout<<(1<<tree.query(b,c).count())<<endl;
    }
}
