/*
@一、反演的概念@
@设在平面内给定一点O和常数k(k不等于零),对于平面内任意一点A,@
@确定A′,使A′为直线OA上一点,并且有向线段OA与OA′满足$OA·OA′=k$,我们称这种变换是以O为反演中心,@
@以k为反演幂的反演变换,简称反演.称A′为A关于O(r)的互为反演点.@
@二、作已知点的反演点的方法@
@给出反演极O和反演幂k>0,作点A的反演点A′.@
@令$k=r^2$,作出反演基圆⊙O(r),@
@1)若点A在⊙O(r)外,则过点A作圆的切线(两条),两个切点相连与OA连线交点就是点A′.@
@2)若点A在⊙O(r)内,则把上述过程逆过来:@
@  连结OA,过点A作直线垂直于OA,直线与⊙O(r)的交点处的切线的交点就是点A′.@
@3)若点A在⊙O(r)上,反演点A′就是点A自身.@
@4)O没有反演点@
@三、圆的反演变换@
@圆在不同情形下的反演成像:@
@1. 当圆不经过反演中心,它的反演图形仍旧是个不过反演中心的圆,并且反演中心为这两个互为反形的圆的位似中心:@
@2. 当圆与反演圆相交,交点是保持不变的;@
@3. 当圆在反演圆的外面的时候,反演成像位于圆的内部;反之,当圆位于反演圆的内部,反演成像位于圆的外部.@
@4. 当圆经过反演中心,它的反演图形是一条直线.@
    @反之,任意一条不过反演中心的直线,其反演成像是一个经过反演中心的圆.@
@5. 相切两圆反向任相切,且切点不变,若切点是反演中心,@
    @则其反象是两条平行直线;两圆相切,若反演中心在某圆上,则为反形为相切的直线与圆;@
*/
//@c1关于c0的反演圆:@
circle getinvertcir(circle c1, circle c0){ 
  circle c2;
  db x0 = c0.o.x, y0 = c0.o.y, r0 = c0.r, 
  db x1 = c1.o.x, y1 = c1.o.y, r1 = c1.r;
  db d01 = dis(c0.o, c1.o);
  c2.r = 0.5*((1/(d01-r1))-(1/(d01+r1)))*r0*r0;
  db d02 = r0*r0/(d01+r1)+c2.r;
  //db _d02 = r0*r0/(d01-r1)-c2.r;
  c2.o.x = x0 + d02/d01*(x1-x0);
  c2.o.y = y0 + d02/d01*(y1-y0);
  return c2;
}
//@直线k1关于c0的反演圆:@
circle getinvertcir(line k1, circle c0){ 
  point a = proj(c0.o, k1[0], k1[1]);
  db oa = dis(c0.o, a);
  db ob = c0.r*c0.r/oa;
  point v = a-c0.o;  v = v/v.len();
  point b = c0.o+v*ob;
  circle res;
  res.o = midpo(c0.o, b);
  res.r = ob/2;
  return res;
}
//@c1关于c0的反演直线:@
line getinvertline(circle c1, circle c0){ 
  point v = c1.o - c0.o;
  v = v / v.len();
  db d = c0.r*c0.r / (2*c1.r);
  point k1 = v * d + c0.o;
  v = v.turn90();
  point k2 = k1 + v;
  return line(k1, k2);
}
//@p关于c的反演点:@
point getinvertpoint(point p, circle c){ 
  point v = (p-c.o).unit();
  db len = c.r*c.r/dis(c.o, p);
  return c.o+v*len;
}
