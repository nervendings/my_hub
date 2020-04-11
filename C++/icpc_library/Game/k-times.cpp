
#include <iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2000000;
int a[maxn],b[maxn];
int main()
{
    int t,n,k;
    cin>>t;
    for(int cas=1;cas<=t;cas++)
    {
        cin>>n>>k;  //@n个石子 每次拿前一次的最多k倍@
        printf("Case %d: ",cas);
        if(n<=k+1)
        {
            printf("lose\n");
            continue;
        }
        a[0]=b[0]=1;
        int i=0,j=0;
        while(a[i]<n)
        {
            i++;
            a[i]=b[i-1]+1;
            while(a[j+1]*k<a[i]) j++;
            if(a[j]*k<a[i]) b[i]=b[j]+a[i];
            else b[i]=a[i];
        }

        if(a[i]==n)printf("lose\n");
        else
        {
            int ans=0;
            while(n)
            {
                if(n>=a[i])
                {
                    n-=a[i];
                    ans=a[i];
                }
                i--;
            }
            cout<<ans<<endl;
        }
    }
}
