// 依赖 3D_Geometry_Relation.cpp。
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
  
  
