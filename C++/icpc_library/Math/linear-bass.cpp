template<typename T,const int len> class lbass{public:
	T d[len+1];int cnt;bool flag;
	void init(){flag=0;memset(d,0,sizeof d);}
	bool insert(T x){
		for(int i=len;x&&i>=0;--i)
      if((T)1<<i&x){
        if(!d[i]) {d[i]=x;return true;}
        else x^=d[i];
      }
    flag=1;
		return false;
	}
	//@线性基和x异或的最值@
	T querymax(T x=0){
    per(i,0,len)x=max(x,x^d[i]);
    return x;
	}
	T querymin(T x=0){
    per(i,0,len)x=min(x,x^d[i]);
    return x;
	}
	//@求所有异或值去重后的第k大,需要预处理@
	T p[len+1];
	void makekth(){
    cnt=0;
    memset(p,0,sizeof p);
    T ans=0;
    per(i,0,len)per(j,0,i-1)
      if((T)1<<j&d[i]) d[i]^=d[j];
    rep(i,0,len) if(d[i]) p[cnt++]=d[i];
	}
	T querykth(T k){
	  if(flag)--k;//@包含零@
	  if(!k) return 0;
	  T res=0;
	  if(k>=(T)1<<cnt) return -1;
	  per(i,0,len) if((T)1<<i&k)res^=p[i];
	  return res;
	}
};
template<typename T,const int len> lbass<T,len> merge(const lbass<T,len> &a,const lbass<T,len> &b){
  lbass<T,len>res=a;
  rep(i,0,len) res.insert(b.d[i]);
  return res;
}
