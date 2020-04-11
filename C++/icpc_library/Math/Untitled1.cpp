#include <bits/stdc++.h>
#define ll long long
using namespace std;
const double pi=acos(-1);
struct cn{
    double x,y;
    cn (double x=0,double y=0):x(x),y(y) {}
}ans[400005];
int a[100005];
ll sum[400005];
cn operator + (const cn &a,const cn &b) {return cn(a.x+b.x,a.y+b.y);}
cn operator - (const cn &a,const cn &b) {return cn(a.x-b.x,a.y-b.y);}
cn operator * (const cn &a,const cn &b) {return cn(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
void fft(cn a[],int n,int l,int f){                                                                                
    int rev[n+5];
    rev[0]=0;
    for (int i=1; i<n; i++){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<l-1);
        if (i<rev[i]) swap(a[i],a[rev[i]]);
    }
    for (int i=1; i<n; i<<=1){
        cn wi(cos(pi/i),f*sin(pi/i));
        for (int j=0; j<n; j+=i*2){
            cn w(1,0);
            for (int k=0; k<i; k++){
                cn x=a[j+k],y=w*a[j+k+i];
                a[j+k]=x+y;
                a[j+k+i]=x-y;
                w=w*wi;
            }
        }
    }
    if (f==-1) for (int i=0; i<n; i++) { a[i].x/=n; a[i].y/=n; }
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		memset(ans,0,sizeof(ans));
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
			ans[a[i]].x++;
		}
		int l=18,N=262144;
	    fft(ans,N,l,1);
	    for (int i=0; i<N; i++) ans[i]=ans[i]*ans[i];
	    fft(ans,N,l,-1);
	    ll ret=0;
		    
	}
}
