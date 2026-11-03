// 依赖 3D_Geometry_Base.cpp。
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
