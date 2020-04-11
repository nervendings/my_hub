#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
struct point{
    ll x, y;
    point(ll _x = 0, ll _y = 0){x = _x, y = _y;}
    void print1(){printf("%lld %lld ", x, y);}
    void print2(){printf("%lld %lld\n", x, y);}
    bool operator < (const point &other) const {
        if(x == other.x) return y < other.y;
        return x < other.x;
    }
    bool operator == (const point &other) const {
        return x == other.x && y == other.y;
    }
};

vector<point>veca, vecb;

ll dis(point a, point b){
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

void solve(ll rr, ll r, ll d, vector<point>&A){
	for (ll i = 1;i*i<= rr; i++){/*@枚举rr内的平方数@*/
		ll t = rr - i*i;
		ll j = sqrt(t);
		if(j*j != t) continue;/*@两个数都应该为平方数@*/
		if(i >= j) break;/*@防止重复枚举@*/
		if(__gcd(i*i, t) == 1){/*@这样求出来的整点都是第一象限的，然后旋转一下@*/
            ll x = i*j*d;
            ll y = sqrt(r*r-x*x);
            A.pb(point(x, y));
            A.pb(point(-x, y));
            A.pb(point(x, -y));
            A.pb(point(-x, -y));
		}
	}
}

void deal(vector<point>&A, ll r){/*@返回半径为r的圆上的整点@*/
    A.pb(point(0, r));
	A.pb(point(0, -r));
	A.pb(point(-r, 0));
	A.pb(point(r, 0));
	r <<= 1;
	for (ll d = 1;d*d <= r; d++){/*@枚举因子@*/
		if(r%d != 0) continue;
		solve(r/d, r>>1, d, A);
		if(d*d== r) break;
		solve(d, r>>1, r/d, A);
	}
}

struct node{
    point A, B;
    node(point _A, point _B){A = _A; B = _B;}
    bool operator < (const node &other) const {
        if(A == other.A) return B < other.B;
        else return A < other.A;
    }
};
vector<node>ans;
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        veca.clear();
        vecb.clear();
        ans.clear();
        ll a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        deal(veca, a);
        deal(vecb, b);
        for(int i = 0; i < veca.size(); i++){
            for(int j = 0; j < vecb.size(); j++){
                if(dis(veca[i], vecb[j]) == c*c){
                    ans.pb(node(veca[i], vecb[j]));
                }
            }
        }
        sort(ans.begin(), ans.end());
        printf("%d\n", ans.size());
        for(int i = 0; i < ans.size(); i++){
            ans[i].A.print1();
            ans[i].B.print2();
        }
    }
}
