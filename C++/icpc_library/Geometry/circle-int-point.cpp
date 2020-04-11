struct point{
  ll x,y;//@两圆上整数点对@
  point(ll _x=0,ll _y=0){x=_x,y=_y;}
  void print2(){printf("%lld %lld\n",x,y);}
  void print1(){printf("%lld %lld ",x,y);}
  bool operator==(const point&other)const{
    return x==other.x&&y==other.y;
  }
  bool operator<(const point&other)const{
    if(x==other.x) return y<other.y;
    return x<other.x;
  }
};
ll dis(point a, point b){
  return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
bool check(ll n){ll x=sqrt(n);return x*x==n;}
void solve(ll rr,ll r,ll d,vector<point>&A){
	for (ll i=1;i*i<=rr;++i){
		ll t=rr-i*i;
		if(!check(t))continue;
		ll j=sqrt(t);
		if(i>=j)break;
		if(__gcd(i*i,t)==1){
      ll x=i*j*d;
      ll y=sqrt(r*r-x*x);
      A.pb(point(x,y));
      A.pb(point(-x,y));
      A.pb(point(x,-y));
      A.pb(point(-x,-y));
		}
	}
}
void deal(vector<point>&A,ll r){
  A.pb(point(0,r));
	A.pb(point(0,-r));
	A.pb(point(-r,0));
	A.pb(point(r,0));
	r<<=1;
	for (ll d=1;d*d<=r;d++){
		if(r%d!=0) continue;
		solve(r/d,r/2,d,A);
		if(d*d==r) break;
		solve(d,r/2,r/d,A);
	}
}
vector<point>veca,vecb;
struct node{
  point A,B;
  node(point _A,point_B){A=_A;B=_B;}
  bool operator<(const node&other)const{
    if(A==other.A)return B<other.B;
    else return A<other.A;
  }
};
vector<node>ans;
int main(){
  int T;ll a,b,c;
  scanf("%d",&T);
  while(T--){
    veca.clear();vecb.clear();ans.clear();
    scanf("%lld%lld%lld",&a,&b,&c);
    deal(veca,a);deal(vecb,b);
    for(int i=0;i<veca.size();i++)
      for(int j=0;j<vecb.size();j++)
        if(dis(veca[i],vecb[j])==c*c)
          ans.pb(node(veca[i],vecb[j]));
    sort(ans.begin(),ans.end());
    printf("%d\n",ans.size());
    for(int i=0;i<ans.size();++i){
      ans[i].A.print1();ans[i].B.print2();
    }
  }
}
