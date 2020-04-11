namespace dsegtree{
#define nd node[now]
#define ndl node[node[now].son[0]]
#define ndr node[node[now].son[1]]
	struct dsegnode{int son[2],sum;}node[maxn*200];
  int cnt;
	int pos,s,t,x;
	void update(int l,int r,int &now){
		if(!now) now=++cnt;
    nd.sum+=x;
		if(l==r) return ;
		if(pos<=((l+r)>>1)) update(l,(l+r)>>1,nd.son[0]);
		else  update(1+((l+r)>>1),r,nd.son[1]);
	}
	void update_1(int _pos,int _x,int &root){
    pos=_pos,x=_x;
    update(1,n,root);
	}
	int query(int l,int r,int now){
    if(!now||nd.sum==0)return 0;
    if(s<=l&&t>=r) return nd.sum;
    int mid=(l+r)>>1;
    int sum=0;
    if(nd.son[0]&&s<=mid)sum+=query(l,mid,nd.son[0]);
    if(nd.son[1]&&t>mid) sum+=query(mid+1,r,nd.son[1]);
    return sum;
	}
	int query_1(int _s,int _t,int root){
	  s=_s,t=_t;
    return query(1,n,root);
	}
}
namespace bit{
	int node[maxn];
	inline void update(int pos,int y,int val){
		for(;pos<=n;pos+=pos&(-pos))
      dsegtree::update_1(y,val,node[pos]);
	}
	inline int ask(int pos,int x,int y){
		int sum=0;
		for(;pos;pos-=pos&(-pos))
			sum+=dsegtree::query_1(x,y,node[pos]);
		return sum;
	}
	inline int query(int l,int r,int x,int y){
		return ask(r,x,y)-ask(l-1,x,y);
	}
}
int aa[maxn];
int main() {
  cin>>n>>m;
  rep(i,1,n) {
    cin>>aa[i];
    if(aa[i]!=aa[i-1]) bit::update(i,aa[i],1);
  }
  register int x,y,b,c,d,e,a;
  while(m--){
    cin>>a;
    if(a==1){
      cin>>x>>y;
      if(aa[x]==y) continue;
      if(aa[x]!=aa[x-1]) bit::update(x,aa[x],-1);
      if(x+1<n&&aa[x+1]!=aa[x]) bit::update(x+1,aa[x+1],-1);
      aa[x]=y;
      if(aa[x]!=aa[x-1]) bit::update(x,aa[x],1);
      if(x+1<n&&aa[x+1]!=aa[x]) bit::update(x+1,aa[x+1],1);
    }else {
      cin>>b>>c>>d>>e;
      int ans=bit::query(b,c,d,e);
      if(aa[b]==aa[b-1]&&aa[b]>=d&&aa[b]<=e) ans++;
      cout<<ans<<endl
    }
  }
}
