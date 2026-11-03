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


