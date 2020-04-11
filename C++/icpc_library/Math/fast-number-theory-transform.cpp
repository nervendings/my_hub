const ll mod=998244353,modg=3,modi=332748118;
int a[maxn],b[maxn];
int pow_mod(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ll)ans*a%mod;
		a=(ll)a*a%mod,b>>=1;
	}
	return ans;
}
int add(int a,int b){
	a+=b;if(a>mod) return a-mod;
	return a;
}
int sub(int a,int b){
	a-=b;if(a<0) return a+mod;
	return a;
}
#define arr vector<int>
const int maxl=2e4+10;//@卷积单个数组的最大长度@
arr operator*(arr&,arr&b){
	int len=a.size();
	arr c(len));
	rep(i,0,len-1) c[i]=a[i]*b[i];
	return c;
}
class nubmer{public:
	int rev[maxl<<2],len,pw;
	int wt[2][maxl<<2];
	void init_0(){
		int len=1;//@最开始的初始化,整个程序一次就够@
		while(len<=maxl) len<<=1;
		for(int mid=1;mid<len;mid<<=1){
			ll wn1=pow_mod(modg,(mod-1)/(mid<<1));
			ll wn2=pow_mod(modi,(mod-1)/(mid<<1));
			wt[0][mid]=wt[1][mid]=1;
			ll wt1=wn1,wt2=wn2;
			rep(j,1,mid){
				wt[0][mid+j]=wt1;wt1=wt1*wn1%mod;
				wt[1][mid+j]=wt2;wt2=wt2*wn2%mod;
			}
		}
	}
	void init(int n){
		len=1,pw=0;
    while(len<=n) len<<=1,++pw;--pw;
    rep(i,0,len-1) rev[i]=rev[i>>1]>>1|(i&1)<<pw;
	}
	void transform(arr &a,int flag){
		ll* f=flag==1?wt[0]:wt[1];
		if(a.size()!=len) a.resize(len);
		rep(i,0,len-1) if(i<rev[i]) swap(a[i],a[rev[i]]);
		for(int mid=1;mid<len;mid<<=1){
			for(int r=mid<<1,j=0;j<len;j+=r){
				ll *p=f+mid;
				for(int k=0;k<mid;++k,++p){
					int x=a[j+k],y=(*p)*a[j+k+mid]%mod;
					a[j+k+mid]=sub(a[j+k],y),a[j+k]+=y;
					if(a[j+k]>mod) a[j+k]-=mod;
				}
			}
		}
		if(flag==-1) {
			ll inv=pow_mod(len,mod-2);
			rep(i,0,len-1){
				a[i]=a[i]*inv%mod;
				if(a[i]<0)a[i]+=mod;
			}
		}
	}
	void fix(arr &a){//@分治ntt优化@
		while(!a.empty()&&!a.back()) a.pop_back();
	}//@会破坏掉a,b数组,视情况可以去掉引用@
	arr mul(arr &a,arr &b){
		int la=a.size(),lb=b.size();
		if(la*lb<=1000){
			arr c(la+lb,0);
			rep(i,0,la-1) rep(j,0,lb-1)
				c[i+j]=(c[i+j]+(ll)a[i]*b[j])%mod;
			return c;
		}
		int n=la+lb;
		init(n);
		transform(a,1);transform(b,1);
		arr c=a*b;
		rep(i,0,len-1)c[i]=(ll)a[i]*b[i]%mod;
		transform(c,-1);
		return c;
	}

}ntt;
