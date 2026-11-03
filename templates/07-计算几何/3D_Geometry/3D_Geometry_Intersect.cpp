// 依赖 3D_Geometry_Position.cpp。
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
  
  
