// https://github.com/zjhl2/ACM-template/blob/938656175f787f0e5d1103c10c08587749635c6a/计算几何/三维计算几何.cpp

#include <math.h>  
#define zero(x) (((x)>0?(x):-(x))<eps)  
constexpr double eps = 1e-8;


struct point3{double x,y,z;};  
struct line3{point3 a,b;};  
struct plane3{point3 a,b,c;};  


//计算cross product U x V  
point3 xmult(point3 u,point3 v){  
    point3 ret;  
    ret.x=u.y*v.z-v.y*u.z;  
    ret.y=u.z*v.x-u.x*v.z;  
    ret.z=u.x*v.y-u.y*v.x;  
    return ret;  
}  

//计算dot product U . V  
double dmult(point3 u,point3 v){  
    return u.x*v.x+u.y*v.y+u.z*v.z;  
}  

//矢量差 U - V  
point3 subt(point3 u,point3 v){  
    point3 ret;  
    ret.x=u.x-v.x;  
    ret.y=u.y-v.y;  
    ret.z=u.z-v.z;  
    return ret;  
}  

double vlen(point3 a) {
    return sqrtl(a.x * a.x + a.y * a.y + a.z * a.z);
}


//取平面法向量  
point3 pvec(plane3 s){  
    return xmult(subt(s.a,s.b),subt(s.b,s.c));  
}  
point3 pvec(point3 s1,point3 s2,point3 s3){  
    return xmult(subt(s1,s2),subt(s2,s3));  
}  


//判三点共线  
int dots_inline(point3 p1,point3 p2,point3 p3){  
    return vlen(xmult(subt(p1,p2),subt(p2,p3)))<eps;  
}  


//判四点共面  
int dots_onplane(point3 a,point3 b,point3 c,point3 d){  
    return zero(dmult(pvec(a,b,c),subt(d,a)));  
}  


//判点是否在线段上,包括端点和共线  
int dot_online_in(point3 p,line3 l){  
    return zero(vlen(xmult(subt(p,l.a),subt(p,l.b))))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&  
        (l.a.y-p.y)*(l.b.y-p.y)<eps&&(l.a.z-p.z)*(l.b.z-p.z)<eps;  
}  
int dot_online_in(point3 p,point3 l1,point3 l2){  
    return zero(vlen(xmult(subt(p,l1),subt(p,l2))))&&(l1.x-p.x)*(l2.x-p.x)<eps&&  
        (l1.y-p.y)*(l2.y-p.y)<eps&&(l1.z-p.z)*(l2.z-p.z)<eps;  
}  
  
  
//判点是否在线段上,不包括端点  
int dot_online_ex(point3 p,line3 l){  
    return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y)||!zero(p.z-l.a.z))&&  
        (!zero(p.x-l.b.x)||!zero(p.y-l.b.y)||!zero(p.z-l.b.z));  
}  
int dot_online_ex(point3 p,point3 l1,point3 l2){  
    return dot_online_in(p,l1,l2)&&(!zero(p.x-l1.x)||!zero(p.y-l1.y)||!zero(p.z-l1.z))&&  
        (!zero(p.x-l2.x)||!zero(p.y-l2.y)||!zero(p.z-l2.z));  
}  
  
  
//判点是否在空间三角形上,包括边界,三点共线无意义  
int dot_inplane_in(point3 p,plane3 s){  
    return dots_onplane(s.a,s.b,s.c,p)&&zero(vlen(xmult(subt(s.a,s.b),subt(s.a,s.c)))-vlen(xmult(subt(p,s.a),subt(p,s.b)))-  
        vlen(xmult(subt(p,s.b),subt(p,s.c)))-vlen(xmult(subt(p,s.c),subt(p,s.a))));  
}  
int dot_inplane_in(point3 p,point3 s1,point3 s2,point3 s3){  
    return dots_onplane(s1,s2,s3,p)&&zero(vlen(xmult(subt(s1,s2),subt(s1,s3)))-vlen(xmult(subt(p,s1),subt(p,s2)))-  
        vlen(xmult(subt(p,s2),subt(p,s3)))-vlen(xmult(subt(p,s3),subt(p,s1))));  
}  
  
  
//判点是否在空间三角形上,不包括边界,三点共线无意义  
int dot_inplane_ex(point3 p,plane3 s){  
    return dot_inplane_in(p,s)&&vlen(xmult(subt(p,s.a),subt(p,s.b)))>eps&&  
        vlen(xmult(subt(p,s.b),subt(p,s.c)))>eps&&vlen(xmult(subt(p,s.c),subt(p,s.a)))>eps;  
}  
int dot_inplane_ex(point3 p,point3 s1,point3 s2,point3 s3){  
    return dot_inplane_in(p,s1,s2,s3)&&vlen(xmult(subt(p,s1),subt(p,s2)))>eps&&  
        vlen(xmult(subt(p,s2),subt(p,s3)))>eps&&vlen(xmult(subt(p,s3),subt(p,s1)))>eps;  
}  
  
  
//判两点在线段同侧,点在线段上返回0,不共面无意义  
int same_side(point3 p1,point3 p2,line3 l){  
    point3 a=xmult(subt(l.a,l.b),subt(p1,l.b)),b=xmult(subt(l.a,l.b),subt(p2,l.b));
    return vlen(a)>=eps&&vlen(b)>=eps&&dmult(a,b)>0;  
}  
int same_side(point3 p1,point3 p2,point3 l1,point3 l2){  
    point3 a=xmult(subt(l1,l2),subt(p1,l2)),b=xmult(subt(l1,l2),subt(p2,l2));
    return vlen(a)>=eps&&vlen(b)>=eps&&dmult(a,b)>0;  
}  
  
  
//判两点在线段异侧,点在线段上返回0,不共面无意义  
int opposite_side(point3 p1,point3 p2,line3 l){  
    point3 a=xmult(subt(l.a,l.b),subt(p1,l.b)),b=xmult(subt(l.a,l.b),subt(p2,l.b));
    return vlen(a)>=eps&&vlen(b)>=eps&&dmult(a,b)<0;  
}  
int opposite_side(point3 p1,point3 p2,point3 l1,point3 l2){  
    point3 a=xmult(subt(l1,l2),subt(p1,l2)),b=xmult(subt(l1,l2),subt(p2,l2));
    return vlen(a)>=eps&&vlen(b)>=eps&&dmult(a,b)<0;  
}  
  
  
//判两点在平面同侧,点在平面上返回0  
int same_side(point3 p1,point3 p2,plane3 s){  
    double a=dmult(pvec(s),subt(p1,s.a)),b=dmult(pvec(s),subt(p2,s.a));
    return !zero(a)&&!zero(b)&&(a>0)==(b>0);  
}  
int same_side(point3 p1,point3 p2,point3 s1,point3 s2,point3 s3){  
    double a=dmult(pvec(s1,s2,s3),subt(p1,s1)),b=dmult(pvec(s1,s2,s3),subt(p2,s1));
    return !zero(a)&&!zero(b)&&(a>0)==(b>0);  
}  
  
  
//判两点在平面异侧,点在平面上返回0  
int opposite_side(point3 p1,point3 p2,plane3 s){  
    double a=dmult(pvec(s),subt(p1,s.a)),b=dmult(pvec(s),subt(p2,s.a));
    return !zero(a)&&!zero(b)&&(a>0)!=(b>0);  
}  
int opposite_side(point3 p1,point3 p2,point3 s1,point3 s2,point3 s3){  
    double a=dmult(pvec(s1,s2,s3),subt(p1,s1)),b=dmult(pvec(s1,s2,s3),subt(p2,s1));
    return !zero(a)&&!zero(b)&&(a>0)!=(b>0);  
}  
  
  
//判两直线平行  
int parallel(line3 u,line3 v){  
    return vlen(xmult(subt(u.a,u.b),subt(v.a,v.b)))<eps;  
}  
int parallel(point3 u1,point3 u2,point3 v1,point3 v2){  
    return vlen(xmult(subt(u1,u2),subt(v1,v2)))<eps;  
}  
  
  
//判两平面平行  
int parallel(plane3 u,plane3 v){  
    return vlen(xmult(pvec(u),pvec(v)))<eps;  
}  
int parallel(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3){  
    return vlen(xmult(pvec(u1,u2,u3),pvec(v1,v2,v3)))<eps;  
}  
  
  
//判直线与平面平行  
int parallel(line3 l,plane3 s){  
    return zero(dmult(subt(l.a,l.b),pvec(s)));  
}  
int parallel(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){  
    return zero(dmult(subt(l1,l2),pvec(s1,s2,s3)));  
}  
  
  
//判两直线垂直  
int perpendicular(line3 u,line3 v){  
    return zero(dmult(subt(u.a,u.b),subt(v.a,v.b)));  
}  
int perpendicular(point3 u1,point3 u2,point3 v1,point3 v2){  
    return zero(dmult(subt(u1,u2),subt(v1,v2)));  
}  
  
  
//判两平面垂直  
int perpendicular(plane3 u,plane3 v){  
    return zero(dmult(pvec(u),pvec(v)));  
}  
int perpendicular(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3){  
    return zero(dmult(pvec(u1,u2,u3),pvec(v1,v2,v3)));  
}  
  
  
//判直线与平面垂直  
int perpendicular(line3 l,plane3 s){  
    return vlen(xmult(subt(l.a,l.b),pvec(s)))<eps;  
}  
int perpendicular(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){  
    return vlen(xmult(subt(l1,l2),pvec(s1,s2,s3)))<eps;  
}  
  
  
//判两线段相交,包括端点和部分重合  
int intersect_in(line3 u,line3 v){  
    if (!dots_onplane(u.a,u.b,v.a,v.b))  
        return 0;  
    if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))  
        return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);  
    return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);  
}  
int intersect_in(point3 u1,point3 u2,point3 v1,point3 v2){  
    if (!dots_onplane(u1,u2,v1,v2))  
        return 0;  
    if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))  
        return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);  
    return dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u2);  
}  
  
  
//判两线段相交,不包括端点和部分重合  
int intersect_ex(line3 u,line3 v){  
    return dots_onplane(u.a,u.b,v.a,v.b)&&opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);  
}  
int intersect_ex(point3 u1,point3 u2,point3 v1,point3 v2){  
    return dots_onplane(u1,u2,v1,v2)&&opposite_side(u1,u2,v1,v2)&&opposite_side(v1,v2,u1,u2);  
}  
  
  
//判线段与空间三角形相交,包括交于边界和(部分)包含  
int intersect_in(line3 l,plane3 s){  
    if (dots_onplane(l.a,s.a,s.b,s.c)&&dots_onplane(l.b,s.a,s.b,s.c))
        return dot_inplane_in(l.a,s)||dot_inplane_in(l.b,s)||intersect_in(l.a,l.b,s.a,s.b)||
            intersect_in(l.a,l.b,s.b,s.c)||intersect_in(l.a,l.b,s.c,s.a);
    return !same_side(l.a,l.b,s)&&!same_side(s.a,s.b,l.a,l.b,s.c)&&  
        !same_side(s.b,s.c,l.a,l.b,s.a)&&!same_side(s.c,s.a,l.a,l.b,s.b);  
}  
int intersect_in(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){  
    if (dots_onplane(l1,s1,s2,s3)&&dots_onplane(l2,s1,s2,s3))
        return dot_inplane_in(l1,s1,s2,s3)||dot_inplane_in(l2,s1,s2,s3)||intersect_in(l1,l2,s1,s2)||
            intersect_in(l1,l2,s2,s3)||intersect_in(l1,l2,s3,s1);
    return !same_side(l1,l2,s1,s2,s3)&&!same_side(s1,s2,l1,l2,s3)&&  
        !same_side(s2,s3,l1,l2,s1)&&!same_side(s3,s1,l1,l2,s2);  
}  
  
  
//判线段与空间三角形相交,不包括交于边界和(部分)包含  
int intersect_ex(line3 l,plane3 s){  
    return opposite_side(l.a,l.b,s)&&opposite_side(s.a,s.b,l.a,l.b,s.c)&&  
        opposite_side(s.b,s.c,l.a,l.b,s.a)&&opposite_side(s.c,s.a,l.a,l.b,s.b);  
}  
int intersect_ex(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){  
    return opposite_side(l1,l2,s1,s2,s3)&&opposite_side(s1,s2,l1,l2,s3)&&  
        opposite_side(s2,s3,l1,l2,s1)&&opposite_side(s3,s1,l1,l2,s2);  
}  
  
  
//计算两直线交点,注意事先判断直线是否共面和平行!  
//线段交点请另外判线段相交(同时还是要判断是否平行!)  
point3 intersection(line3 u,line3 v){  
    point3 ret=u.a;  
    point3 a=xmult(subt(u.a,v.a),subt(v.a,v.b)),b=xmult(subt(u.a,u.b),subt(v.a,v.b));
    double t=fabs(b.x)>=fabs(b.y)&&fabs(b.x)>=fabs(b.z)?a.x/b.x:fabs(b.y)>=fabs(b.z)?a.y/b.y:a.z/b.z;  
    ret.x+=(u.b.x-u.a.x)*t;  
    ret.y+=(u.b.y-u.a.y)*t;  
    ret.z+=(u.b.z-u.a.z)*t;  
    return ret;  
}  
point3 intersection(point3 u1,point3 u2,point3 v1,point3 v2){  
    point3 ret=u1;  
    point3 a=xmult(subt(u1,v1),subt(v1,v2)),b=xmult(subt(u1,u2),subt(v1,v2));
    double t=fabs(b.x)>=fabs(b.y)&&fabs(b.x)>=fabs(b.z)?a.x/b.x:fabs(b.y)>=fabs(b.z)?a.y/b.y:a.z/b.z;  
    ret.x+=(u2.x-u1.x)*t;  
    ret.y+=(u2.y-u1.y)*t;  
    ret.z+=(u2.z-u1.z)*t;  
    return ret;  
}  
  
  
//计算直线与平面交点,注意事先判断是否平行,并保证三点不共线!  
//线段和空间三角形交点请另外判断  
point3 intersection(line3 l,plane3 s){  
    point3 a=subt(s.a,s.b),b=subt(s.b,s.c);
    auto det=[](double a,double b,double c,double d){double t=c*d;return fmal(a,b,-t)+fmal(-c,d,t);};
    point3 ret={det(a.y,b.z,a.z,b.y),det(a.z,b.x,a.x,b.z),det(a.x,b.y,a.y,b.x)},q=s.a;
    auto dis=[&](point3 p){p=subt(p,l.a);return max({fabs(p.x),fabs(p.y),fabs(p.z)});};
    for (point3 p:{s.b,s.c}) if (dis(p)<dis(q)) q=p;
    double t=(ret.x*(q.x-l.a.x)+ret.y*(q.y-l.a.y)+ret.z*(q.z-l.a.z))/  
        (ret.x*(l.b.x-l.a.x)+ret.y*(l.b.y-l.a.y)+ret.z*(l.b.z-l.a.z));  
    ret.x=l.a.x+(l.b.x-l.a.x)*t;  
    ret.y=l.a.y+(l.b.y-l.a.y)*t;  
    ret.z=l.a.z+(l.b.z-l.a.z)*t;  
    return ret;  
}  
point3 intersection(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){
    return intersection(line3{l1,l2},{s1,s2,s3});
}  
  
  
//计算两平面交线,注意事先判断是否平行,并保证三点不共线!  
line3 intersection(plane3 u,plane3 v){  
    line3 ret;  
    ret.a=parallel(v.a,v.b,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.a,v.b,u.a,u.b,u.c);  
    ret.b=parallel(v.c,v.a,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.c,v.a,u.a,u.b,u.c);
    if (ret.a.x==ret.b.x&&ret.a.y==ret.b.y&&ret.a.z==ret.b.z) {
        if (!parallel(v.a,v.b,u.a,u.b,u.c)&&!parallel(v.b,v.c,u.a,u.b,u.c)&&!parallel(v.c,v.a,u.a,u.b,u.c)) ret.b=intersection(v.b,v.c,u.a,u.b,u.c);
        else {
            point3 d=parallel(v.a,v.b,u.a,u.b,u.c)?subt(v.a,v.b):parallel(v.b,v.c,u.a,u.b,u.c)?subt(v.b,v.c):subt(v.c,v.a);
            ret.b.x+=d.x;
            ret.b.y+=d.y;
            ret.b.z+=d.z;
        }
        if ((ret.a.x==ret.b.x&&ret.a.y==ret.b.y&&ret.a.z==ret.b.z)||!parallel(ret,u)||!parallel(ret,v)) {
            line3 l;
            point3 p[3]={u.a,u.b,u.c};
            bool ok=false;
            for (int i=0;i<3;i++) if (!parallel(p[i],p[(i+1)%3],v.a,v.b,v.c)) {
                point3 q=intersection(p[i],p[(i+1)%3],v.a,v.b,v.c);
                if (!ok) l.a=q,ok=true;
                else if (q.x!=l.a.x||q.y!=l.a.y||q.z!=l.a.z) {l.b=q;return l;}
            }
            ret.b=ret.a;
            point3 n=xmult(pvec(u),pvec(v));
            double d=vlen(n),t=sqrtl(max({1.L,fabs(ret.a.x),fabs(ret.a.y),fabs(ret.a.z)}));
            ret.b.x+=n.x/d*t;
            ret.b.y+=n.y/d*t;
            ret.b.z+=n.z/d*t;
        }
    }  
    return ret;  
}  
line3 intersection(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3){
    return intersection(plane3{u1,u2,u3},{v1,v2,v3});
}  
  
  
//点到直线距离  
double ptoline(point3 p,line3 l){  
    return vlen(xmult(subt(p,l.a),subt(l.b,l.a)))/vlen(subt(l.a,l.b));  
}  
double ptoline(point3 p,point3 l1,point3 l2){  
    return vlen(xmult(subt(p,l1),subt(l2,l1)))/vlen(subt(l1,l2));  
}  


//点到平面距离  
double ptoplane(point3 p,plane3 s){  
    return fabs(dmult(pvec(s),subt(p,s.a)))/vlen(pvec(s));  
}  
double ptoplane(point3 p,point3 s1,point3 s2,point3 s3){  
    return fabs(dmult(pvec(s1,s2,s3),subt(p,s1)))/vlen(pvec(s1,s2,s3));  
}  
  
  
//直线到直线距离  
double linetoline(line3 u,line3 v){  
    point3 n=xmult(subt(u.a,u.b),subt(v.a,v.b));  
    if (vlen(n)<eps) return ptoline(u.a,v);
    return fabs(dmult(subt(u.a,v.a),n))/vlen(n);  
}  
double linetoline(point3 u1,point3 u2,point3 v1,point3 v2){  
    point3 n=xmult(subt(u1,u2),subt(v1,v2));  
    if (vlen(n)<eps) return ptoline(u1,v1,v2);
    return fabs(dmult(subt(u1,v1),n))/vlen(n);  
}  
  
  
//两直线夹角cos值  
double angle_cos(line3 u,line3 v){  
    return dmult(subt(u.a,u.b),subt(v.a,v.b))/vlen(subt(u.a,u.b))/vlen(subt(v.a,v.b));  
}  
double angle_cos(point3 u1,point3 u2,point3 v1,point3 v2){  
    return dmult(subt(u1,u2),subt(v1,v2))/vlen(subt(u1,u2))/vlen(subt(v1,v2));  
}  
  
  
//两平面夹角cos值  
double angle_cos(plane3 u,plane3 v){  
    return dmult(pvec(u),pvec(v))/vlen(pvec(u))/vlen(pvec(v));  
}  
double angle_cos(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3){  
    return dmult(pvec(u1,u2,u3),pvec(v1,v2,v3))/vlen(pvec(u1,u2,u3))/vlen(pvec(v1,v2,v3));  
}  
  
  
//直线平面夹角sin值  
double angle_sin(line3 l,plane3 s){  
    return dmult(subt(l.a,l.b),pvec(s))/vlen(subt(l.a,l.b))/vlen(pvec(s));  
}  
double angle_sin(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){  
    return dmult(subt(l1,l2),pvec(s1,s2,s3))/vlen(subt(l1,l2))/vlen(pvec(s1,s2,s3));  
}