#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


ll ysf(ll n,ll k,ll num)   //@n为人数 k为每次点名的数 第num个出列的人的序号 0- n-1@
{
    if(k==1)
        return num-1;
    ll ans=0;
    if(num<k)
    {
        ans=(k-1)%(n-num+1);
        ll p=n-num+1;
        for(ll i=2; i<=num; i++)
        {
            ans=(ans+k)%(++p);
        }
    }
    else                                  //@num很大时用乘法加速@
    {
        ans=-1;
        for(ll i=n-num+1; i<=n; i++)
        {
            ll j=min(n,(i-1)+((i-1)-ans+(k-2))/(k-1));
            ans=(ans+k*(j-i+1))%j,i=j;
        }
    }

    return ans;
}
int main()
{
    ll T,T2;
    cin>>T;
    T2=T;
    while (T--)
    {
        ll n, k,num;
        cin>>n>>num>>k;
        cout<<"Case #"<<T2-T<<": "<<ysf(n,k,num)+1<<endl;
    }


}
