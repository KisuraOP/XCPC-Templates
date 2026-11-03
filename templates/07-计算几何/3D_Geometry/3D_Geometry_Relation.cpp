// 依赖 3D_Geometry_Base.cpp。
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
  
  
