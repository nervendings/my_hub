#define add(a,b) ((a+=b)>=mod?a-=mod:a)
class walsh{public:
  void transform_or(ll *a,int len,int flag){
    for(int i=1;i<len;i<<=1)
      for(int p=i<<1,j=0;j<len;j+=p)
        for(int k=0;k<i;++k)
          add(a[i+j+k],flag==1?a[j+k]:mod-a[j+k]);
  }
  void transform_and(ll *a,int len,int flag){
    for(int i=1;i<len;i<<=1)
      for(int p=i<<1,j=0;j<len;j+=p)
        for(int k=0;k<i;++k)
          add(a[j+k],flag==1?a[i+j+k]:mod-a[i+j+k]);
  }
  void transform_xor(ll *a,int len,int flag){
    for(int i=1;i<len;i<<=1)
      for(int p=i<<1,j=0;j<len;j+=p)
        for(int k=0;k<i;++k){
          int x=a[j+k],y=a[i+j+k];
          a[j+k]=(x+y)%mod,a[i+j+k]=(x+mod-y)%mod;
          if(flag==-1)
            a[j+k]=a[j+k]*inv2%mod,a[i+j+k]=1ll*a[i+j+k]*inv2%mod;
        }
  }
}fwt;
int main(){
  cin>>n;n=(1<<n);
  rep(i,0,n-1) cin>>a[i];
  rep(i,0,n-1) cin>>b[i];
  fwt.transform_or(a,n,1),fwt.transform_or(b,n,1);
  rep(i,0,n-1) ans[i]=a[i]*b[i]%mod;
  fwt.transform_or(a,n,-1),fwt.transform_or(b,n,-1);
  fwt.transform_or(ans,n,-1);
  rep(i,0,n-1) cout<<ans[i]<<' ';cout<<endl;
  fwt.transform_and(a,n,1),fwt.transform_and(b,n,1);
  rep(i,0,n-1) ans[i]=a[i]*b[i]%mod;
  fwt.transform_and(a,n,-1),fwt.transform_and(b,n,-1);
  fwt.transform_and(ans,n,-1);
  rep(i,0,n-1) cout<<ans[i]<<' ';cout<<endl;
  fwt.transform_xor(a,n,1),fwt.transform_xor(b,n,1);
  rep(i,0,n-1) ans[i]=a[i]*b[i]%mod;
  fwt.transform_xor(a,n,-1),fwt.transform_xor(b,n,-1);
  fwt.transform_xor(ans,n,-1);
  rep(i,0,n-1) cout<<ans[i]<<' ';cout<<endl;
}
