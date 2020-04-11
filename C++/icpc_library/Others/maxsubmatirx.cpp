/*
@把二维看成一维@
@先枚举行的起点和终点@
@再把起点行和终点行间每一列的数值压缩到每一个点上@
@然后求一个最长连续子段和@
@复杂度$O(n^3)$@
*/
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=1e3+10;
const int maxm=1e6+10;
const int INF=0x3f3f3f3f;
#define ll long long
int casn,n,m,k;
int smax(int a[],int len){
	int mx=0,sub=0;
	for(int i=1;i<=len;i++){
		sub=max(a[i],sub+a[i]);
		mx=max(sub,mx);
	}
	return mx;
}
int arr[maxn];
int dp[maxn][maxn];
int main(){
#define test
#ifdef test
	freopen("in.txt","r",stdin);freopen("out.txt","w",stdout);
#endif

	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				scanf("%d",&dp[i][j]);
			}
		}
		int ans=-INF;
		for(int i=1;i<=n;i++){
			memset(arr,0,sizeof arr);
			for(int j=i;j<=n;j++){
				for(int k=1;k<=n;k++){
					arr[k]+=dp[j][k];
				}
				ans=max(ans,smax(arr,n));
			}
		}
		printf("%d\n",ans);
	}
#ifdef test
	fclose(stdin);fclose(stdout);system("out.txt");
#endif
	return 0;
}
