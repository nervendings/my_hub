namespace bignumbers{
const int maxd=9999,dlen=4;
class bignumber {public:
  int len,a[maxn];
  bignumber(){len=1;memset(a,0,sizeof(a));}
  bignumber(const ll);
  bignumber(const char*);
  bignumber(const bignumber &);
  bignumber &operator=(const bignumber &);
  friend istream& operator>>(istream&,bignumber&);
  bignumber operator+(const bignumber &)const;
  bignumber operator-(const bignumber &)const;
  bignumber operator*(const bignumber &)const;
  bignumber operator/(const int &)const;
  bignumber operator^(const int &)const;
  ll operator%(const ll &)const;
  bool operator>(const bignumber &T)const;
  bool operator>(const int &t)const;
  void print();
};
bignumber::bignumber(const ll b) {
	int c,d=b;len=0;
	memset(a,0,sizeof(a));
	while(d>maxd){
		c=d-(d/(maxd+1))*(maxd+1);
		d=d/(maxd+1);
		a[len++]=c;
	}
	a[len++]=d;
}
bignumber::bignumber(const char *s) {
	int t,k,index,L;
	memset(a,0,sizeof(a));
	L=strlen(s);
	len=L/dlen;
	if(L%dlen)len++;
	index=0;
	for(int i=L-1;i>=0;i-=dlen) {
		t=0,k=i-dlen+1;
		if(k<0)k=0;
		rep(j,k,i)t=t*10+s[j]-'0';
		a[index++]=t;
	}
}
bignumber::bignumber(const bignumber &T):len(T.len) {
	memset(a,0,sizeof(a));
	rep(i,0,len-1)a[i]=T.a[i];
}
bignumber &bignumber::operator=(const bignumber &n) {
	memset(a,0,sizeof(a));
	rep(i,0,n.len-1)a[i]=n.a[i];
	len=n.len;
	return *this;
}
char ch[maxn*dlen];
istream& operator>>(istream &in,bignumber &b) {
	in>>ch;
	int L=strlen(ch);
	int count=0,sum=0;
	for(int i=L-1;i>=0;) {
		int t=1;sum=0;
		for(int j=0;j<4&&i>=0;j++,i--,t*=10)
			sum+=(ch[i] - '0')*t;
		b.a[count++]=sum;
	}
	b.len=count++;
	return in;
}
bignumber bignumber::operator+(const bignumber &T)const {
	bignumber t(*this);
	int big=T.len>len?T.len:len;
	rep(i,0,big-1){
		t.a[i]+=T.a[i];
		if(t.a[i]>maxd)t.a[i+1]++,t.a[i]-=maxd+1;
	}
	if(t.a[big]!=0) t.len=big+1;
	else t.len=big;
	return t;
}
bignumber bignumber::operator-(const bignumber &T)const {
	bool flag;
	bignumber t1,t2;
	if(*this>T) {
		t1=*this;t2=T;flag=0;
	} else {
		t1=T;t2=*this;flag=1;
	}
	int j,big=t1.len;
	rep(i,0,big-1){
		if(t1.a[i]<t2.a[i]) {
			j=i+1;
			while(t1.a[j]==0) j++;
			t1.a[j--]--;
			while(j>i) t1.a[j--]+=maxd;
			t1.a[i]+=maxd+1-t2.a[i];
		} else t1.a[i]-=t2.a[i];
	}
	t1.len=big;
	while(t1.a[t1.len-1]==0&&t1.len>1)
		t1.len--,big--;
	if(flag) t1.a[big-1]=0-t1.a[big-1];
	return t1;
}
bignumber bignumber::operator*(const bignumber &T)const {
	bignumber ret;
	int up,temp,temp1;
	rep(i,0,len-1){
		up=0;
		rep(j,0,T.len-1){
			temp=a[i]*T.a[j]+ret.a[i+j]+up;
			if(temp>maxd) {
				temp1=temp-temp/(maxd+1)*(maxd+1);
				up=temp/(maxd+1),ret.a[i+j]=temp1;
			} else up=0,ret.a[i+j]=temp;
		}
		if(up!=0)ret.a[i+T.len]=up;
	}
	ret.len=len+T.len;
	while(ret.a[ret.len-1]==0&&ret.len>1)ret.len--;
	return ret;
}
bignumber bignumber::operator/(const int &b)const {
	bignumber ret;
	int down=0;
	per(i,0,len-1) {
		ret.a[i]=(a[i]+down*(maxd+1))/b;
		down=a[i]+down*(maxd+1) - ret.a[i]*b;
	}
	ret.len=len;
	while(ret.a[ret.len-1]==0&&ret.len>1) ret.len--;
	return ret;
}
ll bignumber::operator%(const ll &b)const {
	int d=0;
	per(i,0,len-1)
		d=((d*(maxd+1))%b+a[i])%b;
	return d;
}
bignumber bignumber::operator^(const int &n)const {
	if(n==0)return 1;
	if(n==1)return *this;
	bignumber t,ret(1);
	int m=n,i;
	while(m>1) {
		t=*this;
		for(i=1;(i<<1)<=m;i<<=1)t=t*t;
		m-=i,ret=ret*t;
		if(m==1)ret=ret*(*this);
	}
	return ret;
}
bool bignumber::operator>(const bignumber &T)const {
	if(len>T.len)return true;
	else if(len==T.len) {
		int ln=len-1;
		while(a[ln]==T.a[ln]&&ln>=0)ln--;
		if(ln>=0&&a[ln]>T.a[ln]) return true;
		else return false;
	}else return false;
}
bool bignumber::operator>(const int &t)const {
	bignumber b(t);
	return *this>b;
}
void bignumber::print() {
	printf("%d",a[len-1]);
	per(i,0,len-2)printf("%04d",a[i]);
	printf("\n");
}
}using bignumbers::bignumber;
