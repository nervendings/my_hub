//@圆类@
struct circle{
  point o; db r;
  circle(){}
  circle(point _o, db _r){ o = _o, r = _r; }
//@点在圆内判定:@
  bool include(point k){ return cmp(dis(o, k), r) <= 0; }
};
//@求直线与圆的交点 沿着 k2->k3 方向给出 , 相切给出两个:@
vector<point> getcl(circle k1,point k2,point k3){
  point k=proj(k1.o,k2,k3);
  db d=k1.r*k1.r-(k-k1.o).len2();
  if (sign(d)==-1) return {};
  point del=(k3-k2).unit()*sqrt(max((db)0.0, d));
  return {k-del, k+del};
}
//@ 返回两个圆的公切线数量:@
int checkposcc(circle k1,circle k2){
  if (cmp(k1.r,k2.r)==-1) swap(k1,k2);
  db d=dis(k1.o,k2.o);  int w1=cmp(d,k1.r+k2.r),w2=cmp(d,k1.r-k2.r);
  if (w1>0) return 4; //@相离:@
  else if (w1==0) return 3; //@相切:@
  else if (w2>0) return 2;  //@相交:@
  else if (w2==0) return 1;  //@内切:@
  else return 0; //@内含:@
}
//@求两圆交点 沿圆 k1 逆时针给出 , 相切给出两个:@
vector<point> getcc(circle k1,circle k2){
  int pd=checkposcc(k1,k2);
  if(pd==0||pd==4) return {};
  db a=(k2.o-k1.o).len2();
  db cosA=(k1.r*k1.r+a-k2.r*k2.r)/(2*k1.r*sqrt(max(a,(db)0.0)));
  db b=k1.r*cosA;
  db c=sqrt(max((db)0.0,k1.r*k1.r-b*b));
  point k=(k2.o-k1.o).unit(), m=k1.o+k*b, del=k.turn90()*c;
  return {m-del, m+del};
}
//@过圆外一点作圆的切线的切点:@
//@沿圆 k1 逆时针给出@
vector<point> tangentcp(circle k1,point k2){
  db a=(k2-k1.o).len(),b=k1.r*k1.r/a,c=sqrt(max((db)0.0,k1.r*k1.r-b*b));
  point k=(k2-k1.o).unit(),m=k1.o+k*b,del=k.turn90()*c;
  return {m-del, m+del};
}
//@求两圆的外切线:@
vector<line> tangentoutcc(circle k1,circle k2){
  int pd=checkposcc(k1,k2); if (pd==0) return {};
//@内含,返回一条切线@
  if (pd==1){
    point p1=getcc(k1,k2)[0]; point p2=p1+((p1-k1.o).turn90()/(p1-k1.o).len());
    return {(line){p1,p2}};
  }
  if (cmp(k1.r,k2.r)==0){
    point del=(k2.o-k1.o).unit().turn90().getdel();
    return {(line){k1.o-del*k1.r,k2.o-del*k2.r},(line){k1.o+del*k1.r,k2.o+del*k2.r}};
  } else {
    point p=(k2.o*k1.r-k1.o*k2.r)/(k1.r-k2.r);
    vector<point>A=tangentcp(k1,p),B=tangentcp(k2,p);
    vector<line>ans; for (int i=0;i<A.size();i++) ans.push_back((line){A[i],B[i]});
    return ans;
  }
}
//@求两圆的内切线:@
vector<line> tangentincc(circle k1,circle k2){
  int pd=checkposcc(k1,k2); if (pd<=2) return {};
  if (pd==3){
    point p1=getcc(k1,k2)[0]; point p2=p1+((p1-k1.o).turn90()/(p1-k1.o).len());
    return {(line){p1,p2}};
  }
  point p=(k2.o*k1.r+k1.o*k2.r)/(k1.r+k2.r);
  vector<point>A=tangentcp(k1,p),B=tangentcp(k2,p);
  vector<line>ans; for (int i=0;i<A.size();i++) ans.push_back((line){A[i],B[i]});
  return ans;
}
//@求两圆所有切线:@
vector<line> tangentcc(circle k1,circle k2){
  int flag=0; if (k1.r<k2.r) swap(k1,k2),flag=1;
  vector<line>A=tangentoutcc(k1,k2),B=tangentincc(k1,k2);
  for (line k:B) A.push_back(k);
  if (flag) for (line &k:A) swap(k[0],k[1]);
  return A;
}
//@ 圆 k1 与三角形 k2 k3 k1.o 的有向面积交:@
db circleinsarea(circle k1,point k2,point k3){
  point k=k1.o; k1.o=k1.o-k; k2=k2-k; k3=k3-k;
  int pd1=k1.include(k2),pd2=k1.include(k3);
  vector<point>A=getcl(k1,k2,k3);
//@有一个点在圆内或圆上:@
  if (pd1>=0){
//@三角形整个落在圆内,返回三角形的有向面积@
    if (pd2>=0) return cross(k2,k3)/2;
//@三角形的一个点落在圆内,一个点落在圆外@
    else return k1.r*k1.r*rad(A[1],k3)/2+cross(k2,A[1])/2;
//@三角形的一个点落在圆内,一个点落在圆外@
  } else if (pd2>=0){
    return k1.r*k1.r*rad(k2,A[0])/2+cross(A[0],k3)/2;
//@否则,三角形的两个点都落在圆外:@
  }else {
    int pd=cmp(k1.r,disps(k1.o,k2,k3));
//@返回一个扇形面积:@
    if (pd<=0) return k1.r*k1.r*rad(k2,k3)/2;
//@返回两个扇形加一个三角形:@
    else return cross(A[0],A[1])/2+k1.r*k1.r*(rad(k2,A[0])+rad(A[1],k3))/2;
  }
}
//@以k1k2为直径的圆:@
circle getexcir2(point k1, point k2){
  point c = midpo(k1, k2);
  db r = dis(c, k1);
  return circle(c, r);
}
//@三角形的外接圆:@
circle getexcir3(point k1, point k2, point k3){
  point c = getll( midpo(k1, k2),
                   (k1-k2).turn90()+midpo(k1, k2),
                   midpo(k1, k3),
                   (k1-k3).turn90()+midpo(k1, k3));
  db r = dis(c, k1);
  return circle(c, r);
}
//@最小圆覆盖:@
circle mincircover(vector<point>A){
  random_shuffle(A.begin(), A.end()); int n = A.size();
  circle now = circle(A[0], 0);
  for(int i = 0; i < n; i++)if(!now.include(A[i])){
    now = circle(A[i], 0);
    for(int j = 0; j < i; j++)if(!now.include(A[j])){
      now = getexcir2(A[i], A[j]);
      for(int k = 0; k < j; k++) if(!now.include(A[k]))
        now = getexcir3(A[i], A[j], A[k]);
    }
  }
  return now;
}
