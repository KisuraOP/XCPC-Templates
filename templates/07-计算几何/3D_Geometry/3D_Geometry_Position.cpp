// 依赖 3D_Geometry_Base.cpp。
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
  
  
