int main(){
	double k=(1+sqrt(5.0))/2;
	while(scanf("%d%d",&n,&m)!=EOF) {
		if (n>m) swap(n,m);
		int t=m-n; 
		if (n==(int)((double)t*k)) printf("0\n");
		else printf("1\n");
	}
}
