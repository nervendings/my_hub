namespace suffix{
  int tr[maxn],rank[maxn],sa[maxn],h[maxn],has[maxn],n;
  int cmp(int x,int y,int k){
    if(x+k>n||y+k>n)return 0;
    return rank[x]==rank[y]&&rank[x+k]==rank[y+k];
  }
  void getsa(char *s,int _n,int m=233){
    int i,cnt;n=_n;
    for(i=1;i<=n;i++)has[s[i]]=0;
    for(i=0;i<=m;i++)has[i]=0;
    for(i=1;i<=n;i++)has[s[i]]++;
    for(i=1,cnt=0;i<=m;i++)if(has[i])tr[i]=++cnt;
    for(i=1;i<=m;i++)has[i]+=has[i-1];
    for(i=1;i<=n;i++)rank[i]=tr[s[i]],sa[has[s[i]]--]=i;
    for(int k=1;cnt!=n;k<<=1){
      for(i=1;i<=n;i++)has[i]=0;
      for(i=1;i<=n;i++)has[rank[i]]++;
      for(i=1;i<=n;i++)has[i]+=has[i-1];
      for(i=n;i>=1;i--)if(sa[i]>k)tr[sa[i]-k]=has[rank[sa[i]-k]]--;
      for(i=1;i<=k;i++)tr[n-i+1]=has[rank[n-i+1]]--;
      for(i=1;i<=n;i++)sa[tr[i]]=i;
      for(i=1,cnt=0;i<=n;i++)tr[sa[i]]=cmp(sa[i],sa[i-1],k) ? cnt:++cnt;
      for(i=1;i<=n;i++)rank[i]=tr[i];
    }
    fill_n(h,n+2,0);
    for(int i=1;i<=n;i++){
      if(rank[i]==1)continue;
      for(int j=max(1,h[rank[i-1]]-1);;j++){
        if(s[i+j-1]==s[sa[rank[i]-1]+j-1])h[rank[i]]=j;
        else break;
      }
    }
  }
}
