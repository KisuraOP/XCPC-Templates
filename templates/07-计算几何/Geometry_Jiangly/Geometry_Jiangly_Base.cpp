/*
https://github.com/hh2048/XCPC/blob/main/03%20-%20jiangly%E6%A8%A1%E6%9D%BF%E6%94%B6%E9%9B%86/03%20-%20%E6%95%B0%E8%AE%BA%E3%80%81%E5%87%A0%E4%BD%95%E4%B8%8E%E5%A4%9A%E9%A1%B9%E5%BC%8F/09A%20-%20%E5%B9%B3%E9%9D%A2%E5%87%A0%E4%BD%95%EF%BC%88Point%EF%BC%89.cpp
略有修改
*/

template<class T>
struct Point {
    T x, y;
    Point(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}
    
    template<class U>
    operator Point<U>() const {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(Point p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point &operator-=(Point p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator*=(T v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, Point b) {
        return a += b;
    }
    friend Point operator-(Point a, Point b) {
        return a -= b;
    }
    friend Point operator*(Point a, T b) {
        return a *= b;
    }
    friend Point operator*(T a, Point b) {
        return b *= a;
    }
    friend bool operator==(Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }
    friend istream &operator>>(istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend ostream &operator<<(ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T>
T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
Point<T> rotate(Point<T> a) {
    return Point(-a.y, a.x);
}

template<class T>
int sgn(Point<T> a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}

template<class T>
double dist(Point<T> p1, Point<T> p2) {
    return sqrtl(1.0 * (p1.x - p2.x) * (p1.x - p2.x) + 1.0 * (p1.y - p2.y) * (p1.y - p2.y));
}

template<class T>
struct Line {
    Point<T> a, b;
    Line(Point<T> a_ = Point<T>(), Point<T> b_ = Point<T>()) : a(a_), b(b_) {}
};

template<class T>
bool pointOnLineLeft(Point<T> p, Line<T> l) {
    return cross(l.b - l.a, p - l.a) > 0;
}

template<class T>
Point<T> lineIntersection(Line<T> l1, Line<T> l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

template<class T>
bool pointOnLine(Point<T> p, Line<T> l) {
    return cross(p - l.a, l.b - l.a) == 0;
}

template<class T>
bool pointOnSegment(Point<T> p, Line<T> l) {
    return cross(p - l.a, l.b - l.a) == 0 && min(l.a.x, l.b.x) <= p.x && p.x <= max(l.a.x, l.b.x)
    && min(l.a.y, l.b.y) <= p.y && p.y <= max(l.a.y, l.b.y);
}

template<class T>
double distToLine(Point<T> p, Line<T> l) {
    return abs(cross(p - l.a, l.b - l.a)) / dist(l.a, l.b);
}

template<class T> 
double distToSegment(Point<T> p, Line<T> l) {
    if (l.a == l.b) {
        return dist(l.a, p);
    }
    if (dot(p - l.a, l.b - l.a) <= 0) {
        return dist(l.a, p);
    }
    if (dot(p - l.b, l.b - l.a) >= 0) {
        return dist(l.b, p);
    }
    return distToLine(p, l);
}

