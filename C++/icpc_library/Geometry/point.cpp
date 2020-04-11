//@点类与基础@
#define db double
#define pb push_back
const db eps = 1e-7;
const db pi = acos(-1);
const db inf = 1e9;
int sign(db x){ if(fabs(x) < eps) return 0;  return x > 0 ? 1 : -1; }
int cmp(db k1, db k2){ return sign(k1-k2); }
//@k1在k2、k3之间@:
bool inmid(db k1, db k2, db k3){ return sign(k2-k1)*sign(k3-k1) <= 0; }
//@区间相交判定,区间1在区间2前@:
bool intersect(db l1,db r1,db l2,db r2){
  if(l1>r1) swap(l1,r1); if(l2>r2) swap(l2,r2); 
  return cmp(r1,l2)!=-1 && cmp(r2,l1)!=-1;
}
struct point{
	db x, y;
	point(){}
	point(db k1, db k2){ x = k1, y = k2; }
	//@向量加法、点+向量=点:@*/
	point operator + (const point &k1) const { return point(x+k1.x, y+k1.y); }
	//@向量减法、点-点=向量:@*/
	point operator - (const point &k1) const { return point(x-k1.x, y-k1.y); }
	//@向量数乘:@*/
	point operator * (db k1) const { return (point){x*k1, y*k1}; }
  //@向量数除:@*/
  point operator / (db k1) const { return (point){x/k1, y/k1}; }
  //@比较两个点(向量)是否相同:@*/
  bool operator == (const point &k1) const { 
    return cmp(x,k1.x)==0 && cmp(y,k1.y)==0; 
  }
  //@逆时针旋转:@*/
  point turn(db k1){
    return (point){x*cos(k1)-y*sin(k1), x*sin(k1)+y*cos(k1)};
  }
  //@逆时针旋转90度:@*/
  point turn90(){return (point){-y, x};}
  //@比较两个点(向量)的大小:@
  //@x越小则点越小,若x相等,则y越小点越小.可以实现按点的坐标排序@*/
  bool operator < (const point k1) const{
    int a = cmp(x, k1.x);
    if(a == -1) return 1; 
    else if(a == 1) return 0; 
    else return cmp(y,k1.y)==-1;
  }
  //@向量模长:@
  db len(){ return sqrt(x*x+y*y); }
  //@向量模长的平方:@
  db len2(){ return x*x+y*y; }
  //@单位向量:@
  point unit(){ return (*this)/(*this).len(); }
  //@向量的极角:@
  db angle() { return atan2(y, x); }
  //@将点放入第一象限:@
  //@当横坐标为负时,或横坐标为0纵坐标为负时,将点按原点做对称 角度是$[-π/2, π/2]$@
  point getdel(){
    if (sign(x)==-1||(sign(x)==0&&sign(y)==-1)) return (*this)*(-1);
    else return (*this);
  }
  //@判断点是否在1 2象限,或者在x的负半轴上 角度是(0, π]@
  bool getp() const {return sign(y)==1 || (sign(y)==0&&sign(x)==-1); }
  void scan(){cin>>x>>y;}
  void print(){cout<<x<<' '<<y<<'\n'; }
};
//@判断k1 在 [k2,k3] 内:@
bool inmid(point k1, point k2, point k3){
  return inmid(k1.x,k2.x,k3.x) && inmid(k1.y,k2.y,k3.y);
}
//@得到两点中点:@
point midpo(point k1, point k2){ return (k1+k2)/2; }
//@两点距离的平方@
db dis2(point k1, point k2){ 
  return (k1.x-k2.x)*(k1.x-k2.x) + (k1.y-k2.y)*(k1.y-k2.y); 
}
db dis(point k1, point k2){ return sqrt(dis2(k1, k2)); }
//@叉乘:@
db cross(point k1, point k2){ return k1.x*k2.y - k1.y*k2.x; }
//@点乘:@
db dot(point k1, point k2){ return k1.x*k2.x + k1.y*k2.y; }
//@向量夹角:@
db rad(point k1, point k2){ 
  return acos(dot(k1,k2)/k1.len()/k2.len()); 
//return atan2(cross(k1,k2), dot(k1,k2)); 
}
//@极角排序,[-π, π]:@
bool compareangle (point k1,point k2){
  return k1.getp()<k2.getp() || 
        (k1.getp()==k2.getp() && sign(cross(k1,k2))>0);
}
//@k1 k2 k3 逆时针1 顺时针-1 否则0:@
int clockwise(point k1,point k2,point k3){return sign(cross(k2-k1,k3-k1));}
