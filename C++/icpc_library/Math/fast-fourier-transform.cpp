const double pi=acos(-1.0);
struct cp{double x,y;};
cp operator*(cp a,cp b){return {a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
cp operator+(cp a,cp b){return {a.x+b.x,a.y+b.y};}
cp operator-(cp a,cp b){return {a.x-b.x,a.y-b.y};}
#define carr vector<cp>
const int maxl=6e4+10;//@卷积单个数组的最大长度@
class fourier{public:
  int rev[maxl<<2],len,pw;
  vector<cp> wt;
  void init_0(int ml=maxl){
		for(int mid=1;mid<2*ml;mid<<=1){
			wt.resize(mid*2+1);
			cp wn={cos(pi/mid),sin(pi/mid)};
			wt[mid]=(cp){1,0};
			rep(j,1,mid-1) wt[mid+j]=wt[mid+j-1]*wn;
		}
  }
  void init(int n){
    len=1,pw=0;
    while(len<=n) len<<=1,++pw;--pw;
    rep(i,0,len-1) rev[i]=rev[i>>1]>>1|(i&1)<<pw;
  }
  void transform(carr &a,int flag){
  	if(a.size()!=len) a.resize(len,(cp){0,0});
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
  }//@会破坏掉a,b数组,视情况可以去掉引用@
  carr mul(carr &a,carr &b){
    int la=a.size(),lb=b.size();
    if((ll)la*lb<=1000){
      carr c(la+lb,(cp){0,0});
      rep(i,0,la-1) rep(j,0,lb-1) c[i+j]=c[i+j]+a[i]*b[j];
      return c;
    }
    init(la+lb);
    carr c(len,(cp){0,0});
    transform(a,1);transform(b,1);
    rep(i,0,len-1)c[i]=a[i]*b[i];
    transform(c,-1);
    return c;
  }
}fft;
