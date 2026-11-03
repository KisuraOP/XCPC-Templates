/*
https://github.com/cjj490168650/Template/blob/main/Geometry.cpp
略有修改
*/

using std::numeric_limits;
using std::abs, std::max, std::min, std::swap;
using std::pair, std::make_pair;
using std::tuple, std::make_tuple;
using std::vector, std::deque;
using std::set, std::multiset;

using T=double;  //全局数据类型

constexpr T eps=1e-8;
constexpr T INF=numeric_limits<T>::max();
constexpr T PI=3.1415926535897932384l;

// 点与向量
struct Point
{
    T x,y;

    bool operator==(const Point &a) const {return (abs(x-a.x)<=eps && abs(y-a.y)<=eps);}
    bool operator<(const Point &a) const {return x!=a.x?x<a.x:y<a.y;}
    bool operator>(const Point &a) const {return !(*this<a || *this==a);}
    Point operator+(const Point &a) const {return {x+a.x,y+a.y};}
    Point operator-(const Point &a) const {return {x-a.x,y-a.y};}
    Point operator-() const {return {-x,-y};}
    Point operator*(const T k) const {return {k*x,k*y};}
    Point operator/(const T k) const {return {x/k,y/k};}
    T operator*(const Point &a) const {return x*a.x+y*a.y;}  // 点积
    T operator^(const Point &a) const {return x*a.y-y*a.x;}  // 叉积，注意优先级
    int toleft(const Point &a) const {const auto t=(*this)^a; return (t>eps)-(t<-eps);}  // to-left 测试
    T len2() const {return (*this)*(*this);}  // 向量长度的平方
    T dis2(const Point &a) const {return (a-(*this)).len2();}  // 两点距离的平方
    int quad() const // 象限判断 0:原点 1:x轴正 2:第一象限 3:y轴正 4:第二象限 5:x轴负 6:第三象限 7:y轴负 8:第四象限
    {
        if (x==0 && y==0) return 0;
        if (y==0) return x>0 ? 1 : 5;
        if (x==0) return y>0 ? 3 : 7;
        return y>0 ? (x>0 ? 2 : 4) : (x>0 ? 8 : 6);
    }

    // 必须用浮点数
    T len() const {return sqrtl(len2());}  // 向量长度
    T dis(const Point &a) const {return sqrtl(dis2(a));}  // 两点距离
    T ang(const Point &a) const {return atan2l(abs((*this)^a),(*this)*a);}  // 向量夹角
    Point rot(const T rad) const {return {x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad)};}  // 逆时针旋转（给定角度）
    Point rot(const T cosr,const T sinr) const {return {x*cosr-y*sinr,x*sinr+y*cosr};}  // 逆时针旋转（给定角度的正弦与余弦）

    void read() {
        int X, Y; 
        cin >> X >> Y;
        x = X; y = Y;
    }
};

// 极角排序
struct Argcmp
{
    bool operator()(const Point &a,const Point &b) const
    {
        const int qa=a.quad(),qb=b.quad();
        if (qa!=qb) return qa<qb;
        const auto t=a^b;
        // if (abs(t)<=eps) return a*a<b*b-eps;  // 不同长度的向量需要分开
        return t>0;
    }
};

// 直线
struct Line
{
    Point p,v;  // p 为直线上一点，v 为方向向量

    bool operator==(const Line &a) const {return v.toleft(a.v)==0 && v.toleft(p-a.p)==0;}
    int toleft(const Point &a) const {return v.toleft(a-p);}  // to-left 测试
    bool operator<(const Line &a) const  // 半平面交算法定义的排序
    {
        if ((v^a.v)==0 && v*a.v>0) return toleft(a.p)==-1;
        return Argcmp()(v,a.v);
    }

    // 必须用浮点数
    Point inter(const Line &a) const {return p+v*((a.v^(p-a.p))/(v^a.v));}  // 直线交点
    T dis(const Point &a) const {return abs(v^(a-p))/v.len();}  // 点到直线距离
    Point proj(const Point &a) const {return p+v*((v*(a-p))/(v*v));}  // 点在直线上的投影
};

//线段
struct Segment
{
    Point a,b;

    bool operator<(const Segment &s) const {return make_pair(a,b)<make_pair(s.a,s.b);}

    // 判定性函数建议在整数域使用

    // 判断点是否在线段上
    // -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
    int is_on(const Point &p) const  
    {
        if (p==a || p==b) return -1;
        return (p-a).toleft(p-b)==0 && (p-a)*(p-b)<0;
    }

    // 判断线段直线是否相交
    // -1 直线经过线段端点 | 0 线段和直线不相交 | 1 线段和直线严格相交
    int is_inter(const Line &l) const
    {
        if (l.toleft(a)==0 || l.toleft(b)==0) return -1;
        return l.toleft(a)!=l.toleft(b);
    }
    
    // 判断两线段是否相交
    // -1 在某一线段端点处相交 | 0 两线段不相交 | 1 两线段严格相交
    int is_inter(const Segment &s) const
    {
        if (is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b)) return -1;
        const Line l{a,b-a},ls{s.a,s.b-s.a};
        return l.toleft(s.a)*l.toleft(s.b)==-1 && ls.toleft(a)*ls.toleft(b)==-1;
    }

    // 点到线段距离（必须用浮点数）
    T dis(const Point &p) const
    {
        if (a.dis2(b)==0) return p.dis(a);
        if ((p-a)*(b-a)<0 || (p-b)*(a-b)<0) return min(p.dis(a),p.dis(b));
        const Line l{a,b-a};
        return l.dis(p);
    }

    // 两线段间距离（必须用浮点数）
    T dis(const Segment &s) const
    {
        if (is_inter(s)) return 0;
        return min({dis(s.a),dis(s.b),s.dis(a),s.dis(b)});
    }
};

// 射线
struct Ray
{
    Point p, v; // p 为射线原点，v 为方向向量

    // 判断点是否在射线上
    // 0: 不在射线上 | 1: 在射线上（非端点） | -1: 点与射线原点重合
    int is_on(const Point &a) const
    {
        if (a==p) return -1;
        if (Line{p,v}.dis(a)>eps) return 0; // 不共线
        return (a-p)*v>0?1:0; // 方向相同
    }
};

