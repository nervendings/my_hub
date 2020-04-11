class matrix{public://mod
  int a,b;
  vector<vector<ll> > x;
  matrix(int a=1,int b=1){
    this->a=a,this->b=b;x.resize(a);
    for(auto &i:x){i.resize(b);std::fill(all(i),0);}
  }
  void e(int n){a=b=n;x=matrix(n,n).x;for(int i=0;i<n;i++)x[i][i]=1;}
  void fill(ll xx=0){for(int i=0;i<a;i++)for(int j=0;j<b;j++)x[i][j]=xx;}
  void fill(vector<vector<ll>> &y){x=y;a=y.size();b=y[0].size();}
  matrix operator *(matrix &m){
    matrix ans(a,m.b);
    for(int i=0;i<a;i++)for(int j=0;j<m.b;j++)for(int k=0;k<b;k++)if(x[i][k]&&m.x[k][j])
      ans.x[i][j]=(mod+ans.x[i][j]+(x[i][k]*m.x[k][j]+mod)%mod)%mod;
    return ans;
  }
  matrix operator +(matrix &m){
    matrix ans(a,m.b);
    for(int i=0;i<a;i++)for(int j=0;j<b;j++)ans.x[i][j]=(x[i][j]+m.x[i][j]+mod)%mod;
    return ans;
  }
  matrix operator -(matrix &m){
    matrix ans(a,m.b);
    for(int i=0;i<a;i++)for(int j=0;j<b;j++)ans.x[i][j]=(x[i][j]-m.x[i][j]+mod)%mod;
    return ans;
  }
  matrix pow(ll p){
    matrix ans;ans.e(a);matrix t;t.fill(x);
    while(p){if(p&1) ans=t*ans;t=t*t;p>>=1;}return ans;
  }
};

