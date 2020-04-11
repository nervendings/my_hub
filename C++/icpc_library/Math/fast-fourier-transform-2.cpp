const double pi=acos(-1.0);
struct cp{double x,y;};
cp operator*(cp a,cp b){return {a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
cp operator+(cp a,cp b){return {a.x+b.x,a.y+b.y};}
cp operator-(cp a,cp b){return {a.x-b.x,a.y-b.y};}
const int maxl=2e6+10;
class fourier{public:
  int rev[maxl<<2],len,pw;
  void init(int n){
    len=1,pw=0;
    while(len<=n) len<<=1,++pw;--pw;
    rep(i,0,len-1) rev[i]=rev[i>>1]>>1|(i&1)<<pw;
  }
  cp c1[maxl<<2],c2[maxl<<2];
  vector<cp> wt;
  void init_0(){
		for(int mid=1;mid<2*maxl;mid<<=1){
			wt.resize(mid*2+1);
			cp wn{cos(pi/mid),sin(pi/mid)};
			wt[mid]=(cp){1,0};
			rep(j,1,mid-1) wt[mid+j]=wt[mid+j-1]*wn;
		}
  }
  void transform(cp*a,int flag){
    rep(i,0,len-1) if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(int mid=1;mid<len;mid<<=1){
      for(int r=mid<<1,j=0;j<len;j+=r){
        for(int k=0;k<mid;++k){
          cp wn=wt[mid+k];
          if(flag==-1) wn.y=-wn.y;
          cp y=wn*a[mid+j+k];
          a[j+k+mid]=a[j+k]-y,a[j+k]=a[j+k]+y;
        }
      }
    }
    if(flag==-1) rep(i,0,len-1) a[i].x/=len;
  }
  void fix(vector<int>&a){
    while(!a.empty()&&!a.back())a.pop_back();
  }//@传入整数,进行卷积@
  void mul(vector<int> &a,vector<int> &b){
    int la=a.size(),lb=b.size();
    init(la+lb);
    rep(i,0,la-1) c1[i]=(cp){a[i],0};
    rep(i,la,len-1) c1[i]=(cp){0,0};
    rep(i,0,lb-1) c2[i]=(cp){b[i],0};
    rep(i,lb,len-1) c2[i]=(cp){0,0};
    transform(c1,1);transform(c2,1);
    rep(i,0,len-1) c1[i]=c1[i]*c2[i];
    transform(c1,-1);
    a.resize(len);
    rep(i,0,len-1) a[i]=int(c1[i].x+0.5)?1:0;
    fix(a);
  }
  void sqr(vector<int> &a){
    int la=a.size(); init(2*la);
    rep(i,0,la-1)c1[i]=(cp){a[i],0};
    rep(i,la,len-1)c1[i]=(cp){0,0};
    transform(c1,1);
    rep(i,0,len-1) c1[i]=c1[i]*c1[i];
    transform(c1,-1);
    a.resize(len);
    rep(i,0,len-1) a[i]=int(c1[i].x+0.5)?1:0;
    fix(a);
  }
  vector<int> pow(vector<int>a,int k){
    fix(a);
    vector<int>ret;
    while(k){
      if(k&1){
        if(ret.empty()) ret=a;
        else mul(ret,a);
      }
      sqr(a);
      k/=2;
    }
    return ret;
  }
}
