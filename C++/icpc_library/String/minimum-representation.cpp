int minrep(int *s,int n){
  int i=0,j=1,k=0,t;
  while(i<n&&j<n&&k<n){
    t=s[i+k>=n?i+k-n:i+k]-s[j+k>=n?j+k-n:j+k];
    if(!t) ++k;
    else {
      if(t>0) i+=k+1;
      else j+=k+1;
      if(i==j) ++j;
      k=0;
    }
  }
  return min(i,j);
}
