//@直线与线段@
//@直线类@
struct line{ 
//@方向为p[0]->p[1]@
  point p[2];
  line(){}
  line(db x1,db y1,db x2,db y2){p[0]=point(x1,y1),p[1]=point(x2,y2);}
  line(point k1,point k2){p[0]=k1; p[1]=k2;}
  point& operator [] (int k){return p[k];}
//@点在直线左侧的判定:@
//@沿着p0->p1的左侧为1,右侧为0@
  bool include(point k){ 
    return sign(cross(p[0]-k,p[1]-k))>0; 
  } 
//@方向向量:@
  point dir(){return p[1]-p[0];} 
//@向外(左)平移eps@
  line push(){ 
    point delta=(p[1]-p[0]).turn90().unit()*eps;
    return {p[0]-delta, p[1]-delta};
  }
};
//@线段类:@
struct segment{
  point p[2];
  segment(){}
  segment(db x1,db y1,db x2,db y2){p[0]=point(x1,y1),p[1]=point(x2,y2);}
  segment(point a, point b){ p[0]= a, p[1] = b; }
  point dir(){return p[1]-p[0];} 
  point& operator [] (int k){ return p[k]; }
};
//@q 到直线 k1,k2 的投影:@
point proj(point q, point k1, point k2){
  point k=k2-k1; 
  return k1+k*(dot(q-k1,k)/k.len2()); 
} 
//@q 关于直线 k1, k2 的对称点:@
point reflect(point q, point k1, point k2){ 
  return proj(q,k1,k2)*2-q; 
} 
//@点在线段上的判定:@
bool checkons(point q,point k1,point k2){ 
  return inmid(q,k1,k2) && sign(cross(k1-q, k2-k1))==0; 
} 
//@点在直线上的判定:@
bool checkonl(point q,point k1,point k2){ 
  return sign(cross(k1-q, k2-k1))==0; 
} 
//@点在射线k1->k2上的判定:@
bool checkonr(point q, point k1, point k2){ 
  return sign(cross(q-k1, k2-k1)) == 0 && sign(dot(q-k1, k2-k1)) >= 0;
}
//@直线平行判定,可以重合:@
bool parallel(line k1,line k2){ return sign(cross(k1.dir(),k2.dir()))==0; }
//@直线同向判定:@
bool samedir(line k1,line k2){ 
  return parallel(k1,k2)&&sign(dot(k1.dir(),k2.dir()))==1; 
} 
//@直线的比较,极角排序,范围是[-π, π]:@
bool operator < (line k1,line k2){ 
  if (samedir(k1,k2)) return k2.include(k1[0]);
  return compareangle(k1.dir(),k2.dir());
}
//@直线相交判定:@
//@叉积计算面积,两直线不平行必相交(除去重合的情况),平行时,三角形面积相等:@
bool checkll(point k1,point k2,point k3,point k4){ 
  return cmp(cross(k3-k1,k4-k1),cross(k3-k2,k4-k2))!=0;
}
//@直线相交判定:@
bool checkll(line k1,line k2){ 
  return checkll(k1[0],k1[1],k2[0],k2[1]); 
} 
//@直线交点:@
point getll(point k1,point k2,point k3,point k4){ 
  db w1=cross(k1-k3,k4-k3),w2=cross(k4-k3,k2-k3); 
  return (k1*w2+k2*w1)/(w1+w2);
}
//@直线交点:@
point getll(line k1,line k2){
  return getll(k1[0],k1[1],k2[0],k2[1]); 
} 
//@直线与线段相交判定:@
//@线段的两端点在直线的两侧@
bool checkls(point k1, point k2, point k3, point k4){ 
  return sign(cross(k1-k3, k2-k3)) * sign(cross(k1-k4, k2-k4)) <= 0;
}
//@ 线段相交判定:@
bool checkss(point k1,point k2,point k3,point k4){ 
  return intersect(k1.x,k2.x,k3.x,k4.x)&&intersect(k1.y,k2.y,k3.y,k4.y) &&
         sign(cross(k3-k1,k4-k1))*sign(cross(k3-k2,k4-k2))<=0 &&
         sign(cross(k1-k3,k2-k3))*sign(cross(k1-k4,k2-k4))<=0;
}
//@ 线段相交判定:@
bool checkss(segment k1, segment k2){ 
  return checkss(k1[0], k1[1], k2[0], k2[1]); 
}
//@线段规范相交判定:@
//@端点相交不算@
bool strictcheckss(point k1, point k2, point k3, point k4){ 
  return sign(cross(k3-k1,k4-k1))*sign(cross(k3-k2,k4-k2))<0 &&
         sign(cross(k1-k3,k2-k3))*sign(cross(k1-k4,k2-k4))<0;
}
//@ 线段规范相交判定:@
bool strictcheckss(segment k1, segment k2){ 
  return strictcheckss(k1[0], k1[1], k2[0], k2[1]); 
}
//@点到直线的距离:@
db displ(point q, point k1, point k2){ 
  if(k1 == k2) return dis(q, k1);
  return fabs(cross(k2-k1, q-k1)) / (k2-k1).len();
}
//@点到直线的距离:@
db displ(point q, line l){ 
  return displ(q, l[0], l[1]); 
}
//@点到线段的距离:@
db disps(point q,point k1,point k2){
  point k3 = proj(q,k1,k2);
  if (inmid(k3,k1,k2)) return dis(q, k3); 
  else return min(dis(q, k1),dis(q, k2));  
}
//@点到线段的距离:@
db disps(point q, segment k1){ 
  return disps(q, k1[0], k1[0]); 
}
//@线段到线段间的距离:@
db disss(point k1,point k2,point k3,point k4){ 
  if (checkss(k1,k2,k3,k4)) return 0;
  else return min(min(disps(k3,k1,k2),disps(k4,k1,k2)),
                  min(disps(k1,k3,k4),disps(k2,k3,k4)));
}
//@线段到线段间的距离:@
db disss(segment k1, segment k2){ 
  return disss(k1[0], k1[1], k2[0], k2[1]); 
}
