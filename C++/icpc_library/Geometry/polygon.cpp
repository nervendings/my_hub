//@多边形函数@
//@三角形面积:@
db tarea(point a,point b,point c){
  return fabs((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x))/2;
}
//@多边形面积:@
//@多边形用 vector<point> 表示 , 逆时针@
db polyarea(vector<point>A){
  db ans = 0;
  sort(all(A),compareangle);
  for(int i=0;i<A.size();i++) ans += cross(A[i],A[(i+1)%A.size()]);
  return fabs(ans/2);
}
//@多边形周长:@
db polyperimeter(vector<point>&A){
  db ans = 0;
  for(int i = 0; i < A.size(); i++) ans += dis(A[i], A[(i+1)%A.size()]);
  return ans;
}
//@多边形重心:@
point polyfocus(vector<point>&A){
  int n = A.size();
  db sumx= 0, sumy = 0, sumarea = 0, area;
  for(int i = 1; i+1 < n; i++){
    area = cross(A[i]-A[0], A[i+1]-A[0])/2.0;
    sumarea += area;
    sumx += (A[0].x+A[i].x+A[i+1].x)*area;
    sumy += (A[0].y+A[i].y+A[i+1].y)*area;
  }
  return point(sumx/sumarea/3.0, sumy/sumarea/3.0);
}
//@点与多边形的位置关系:@
//@ 2 内部 1 边界 0 外部@
int contain(vector<point>&A, point q){
  int pd=0; A.push_back(A[0]);
  for (int i=1;i<A.size();i++){
    point u=A[i-1], v=A[i];
    if (checkons(q,u,v)) return 1;
    if (cmp(u.y,v.y)>0) swap(u,v);
    if (cmp(u.y,q.y)>=0||cmp(v.y,q.y)<0) continue;
    if (sign(cross(u-v,q-v))<0) pd^=1;
  }
  return pd<<1;
  int wn = 0;
  int n = A.size();
  for(int i = 0; i < n; i++){
    if(checkons(q, A[i], A[(i+1)%n])); return -1;//onside
    int k = sign(cross(A[(i+1)%n]-A[i], q-A[i]));
    int d1 = sign(A[i].y-q.y);
    int d2 = sign(A[(i+1)%n].y-q.y);
    if(k > 0 && d1 <= 0 && d2 > 0) wn++;
    if(k < 0 && d2 <= 0 && d1 > 0) wn--;
  }
  if(wn != 0) return 1;//inside
  return 0;//outside
}
//@逆时针凸包判定:@
int checkconvex(vector<point>&A){
  int n=A.size(); A.pb(A[0]); A.pb(A[1]);
  for (int i=0;i<n;i++) if(sign(cross(A[i+1]-A[i],A[i+2]-A[i]))==-1) return 0;
  return 1;
}
//@求凸包:@
//@flag=0 不严格 flag=1 严格@
vector<point> convexhull(vector<point>A, int flag=1){
  int n=A.size(); vector<point>ans(n*2);
  sort(A.begin(), A.end());
  int now=-1;
//@下凸壳@
  for(int i=0;i<n;i++){
    while(now>0 && sign(cross(ans[now]-ans[now-1], A[i]-ans[now-1])) < flag) now--;
    ans[++now]=A[i];
  }
  int pre=now;
//@上凸壳@
  for(int i=n-2;i>=0;i--){
    while(now>pre && sign(cross(ans[now]-ans[now-1], A[i]-ans[now-1])) < flag) now--;
    ans[++now]=A[i];
  }
//@因为A[0]会被算两次,所以舍弃最后一次的A[0]@
  ans.resize(now);
  return ans;
}
//@切割凸包:@
//@保留直线左边的所有点@
vector<point> convexcut(vector<point>A,point k1,point k2){
  int n=A.size(); A.push_back(A[0]); vector<point>ans;
  for(int i=0;i<n;i++){
    int w1=clockwise(k1,k2,A[i]), w2=clockwise(k1,k2,A[i+1]);
    if (w1>=0) ans.push_back(A[i]);
    if (w1*w2<0) ans.push_back(getll(k1,k2,A[i],A[i+1]));
  }
  return ans;
}
//@凸包最近点对:@
//@先要按照 x 坐标排序@
bool _cmp(point k1,point k2){return k1.y<k2.y;}
db closestpoint(vector<point>&A,int l,int r){
  if (r-l<=5){
//@当点数小于等于5时,暴力计算:@
    db ans=1e20;
    for (int i=l;i<=r;i++) for (int j=i+1;j<=r;j++) ans=min(ans,dis(A[i],A[j]));
    return ans;
  }
  int mid=l+r>>1; db ans=min(closestpoint(A,l,mid),closestpoint(A,mid+1,r));
  vector<point>B; for (int i=l;i<=r;i++) if (abs(A[i].x-A[mid].x)<=ans) B.push_back(A[i]);
  sort(B.begin(),B.end(),_cmp);
  for (int i=0;i<B.size();i++) for (int j=i+1;j<B.size()&&B[j].y-B[i].y<ans;j++) 
    ans=min(ans,dis(B[i],B[j]));
  return ans;
}
//@凸包的直径(最远点对):@
//@旋转卡壳,得到的答案为最远距离的平方@
db convexdiameter(vector<point>&A){
  int n = A.size();
  int now = 1;
  db res = 0;
  for(int i = 0; i < n; i++){
    while(1){
      db x=cross(A[i]-A[(i+1)%n],A[i]-A[(now+1)%n]);
      db y=cross(A[i]-A[(i+1)%n],A[i]-A[now]);
      if(x<y) break;
      now=(now+1)%n;
    }
    res = max(res, dis2(A[now], A[i]));
  }
  return res;
}
//@点集中的最大三角形:@
db maxtriangle(vector<point>&A){
  int m = A.size();
  int a = 1, b = 2;
  db res = 0;
  for(int i = 0; i < m; i++){
		while(cross(A[a]-A[i], A[(b+1)%m]-A[i]) > cross(A[a]-A[i], A[b]-A[i]))
			b = (b + 1) % m;
		res = max(res, cross(A[a]-A[i], A[b]-A[i]) / 2.0);
		while(cross(A[(a+1)%m]-A[i], A[b]-A[i]) > cross(A[a]-A[i], A[b]-A[i]))
			a = (a + 1) % m;
		res = max(res, cross(A[a]-A[i], A[b]-A[i]) / 2.0);
	}
  return res;
}
//@凸包间的最小距离:@
db mindisbetconvex(vector<point>&A, vector<point>&B){
  int n = A.size(), m = B.size();
  if(n < 3 && m < 3){
    if(n == 1){
      if(m == 1) return dis(A[0], B[0]);
      else return disps(A[0], B[0], B[1]);
    }
    else{
      if(m == 1) return disps(B[0], A[0], A[1]);
      else return disss(A[0], A[1], B[0], B[1]);
    }
  }
  int ai = 0, bi = 0;
  for(int i = 0; i < n; i++) if(A[i].y < A[ai].y){ ai = i; }
  for(int i = 0; i < m; i++) if(B[i].y > A[bi].y){ bi = i; }
  db ans = 1e18;
  for(int i  = 0; i < n; i++){
    db ck;
    while(ck = sign(cross(B[(bi+1)%m]-B[bi], A[(ai+1)%n]-A[ai])) < 0) bi = (bi+1)%m;
    if(ck == 0) ans = min(ans, disss(A[(ai+1)%n], A[ai], B[(bi+1)%m], B[bi]));
    else ans = min(ans, disps(B[bi], A[(ai+1)%n], A[ai]));
    ai = (ai+1)%n;
  }
  return ans;
}
//@最小正方形覆盖:@
db minsquarecover(vector<point>&A, db rad){
  db minx = inf, maxx = -inf, miny = inf, maxy = -inf;
  for(int i = 0; i < A.size(); i++){
    point p = A[i].turn(rad);
    minx = min(minx, p.x);
    miny = min(miny, p.y);
    maxx = max(maxx, p.x);
    maxy = max(maxy, p.y);
  }
  return max(maxx-minx, maxy-miny);
}
//@三分--最小正方形覆盖:@
db t_divide(vector<point>&A, db l, db r){
  db m,rm,eps=1e-8;
  while(r-l>=eps){
    m=l+(r-l)/3;
    rm=r-(r-l)/3;
    if(minsquarecover(A,m)>minsquarecover(A,rm)) l=m;
    else r=rm;
  }
  return minsquarecover(A, (m+rm)/2);
}
//@求半平面交:@
//@半平面是逆时针方向 , 输出按照逆时针@
vector<point> gethalf(vector<line> L){
  int n = L.size();
  sort(L.begin(), L.end());
  int first = 0, last = 0;
//@双端队列指针@
  line *q = new line[n];
//@双端队列@
  point *p = new point[n];
//@p[i]为l[i]和l[i+1]的交点@
  q[last] = L[0];
//@初始化为一个半平面@
  for(int i = 0; i < n; i++){
    while(first < last && !L[i].include(p[last-1])) last--;
    while(first < last && !L[i].include(p[first])) first++;
    q[++last] = L[i];
    if(samedir(q[last], q[last-1])) last--;
    if(first < last) p[last-1] = getll(q[last], q[last-1]);
  }
  while(first < last && !q[first].include(p[last-1])) last--;
  vector<point>ans;
  if(last - first <= 1) return ans;
  p[last] = getll(q[last], q[first]);
  for(int i = first; i <= last; i++) ans.pb(p[i]);
  return ans;
}
int checkpos(line k1,line k2,line k3){return k3.include(getll(k1,k2));}
//@求半平面交:@
//@半平面是逆时针方向 , 输出按照逆时针@
vector<line> gethl(vector<line> L){
  sort(L.begin(),L.end()); deque<line> q;
  for (int i=0;i<(int)L.size();i++){
    if (i&&samedir(L[i],L[i-1])) continue;
    while (q.size()>1&&!checkpos(q[q.size()-2],q[q.size()-1],L[i])) q.pop_back();
    while (q.size()>1&&!checkpos(q[1],q[0],L[i])) q.pop_front();
    q.push_back(L[i]);
  }
  while (q.size()>2&&!checkpos(q[q.size()-2],q[q.size()-1],q[0])) q.pop_back();
  while (q.size()>2&&!checkpos(q[1],q[0],q[q.size()-1])) q.pop_front();
  vector<line>ans; for (int i=0;i<q.size();i++) ans.push_back(q[i]);
  return ans;
}
