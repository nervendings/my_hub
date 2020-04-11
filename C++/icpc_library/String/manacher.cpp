class manacher{
  char ma[maxn<<1];int lenp[maxn<<1];
  void getp(char *s,int len){
    int p=0;
    ma[p++]='$',ma[p++]='#';
    forn(i,len) ma[p++]=s[i],ma[p++]='#';
    int r=0,mid=0;
    forn(i,(len+1)<<1){
      lenp[i]=r>i?min(lenp[(mid<<1)-i],r-i):1;
      while(ma[i+lenp[i]]==ma[i-lenp[i]]) lenp[i]++;
      if(i+lenp[i]>r)r=i+lenp[i],mid=i;
    }
  }
}
