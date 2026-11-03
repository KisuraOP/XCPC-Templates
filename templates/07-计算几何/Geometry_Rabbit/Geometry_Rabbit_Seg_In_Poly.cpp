// 依赖 Geometry_Rabbit_Polygon.cpp。
bool in_angle(Point c, Point a, Point b) {
    if (a.toleft(b) > 0) {
        return a.toleft(c) >= 0 && c.toleft(b) >= 0;
    }
    return !(b.toleft(c) > 0 && c.toleft(a) > 0);
}

// 线段是否完全在多边形内
bool seg_in_poly(Segment s, const Polygon &poly) {
    auto a = poly.winding(s.a), b = poly.winding(s.b);
    if (!(a.first || a.second) || !(b.first || b.second)) return false;
    if (s.a == s.b) {
        auto wind = poly.winding(s.a);
        return wind.first || wind.second != 0;
    }
    for (size_t i = 0; i < poly.p.size(); i++) {
        Point u = poly.p[i];
        Point v = poly.p[poly.nxt(i)];
        Point w = poly.p[poly.pre(i)];
        Segment edge = {u, v};
        if (s.is_inter(edge) == 1) {
            return false;
        }
        if (s.is_on(u)) {
            if (!(s.a == u) && !in_angle(s.a - u, v - u, w - u)) return false;
            if (!(s.b == u) && !in_angle(s.b - u, v - u, w - u)) return false;
        } else {
            if (edge.is_on(s.a) == 1 && (s.b - s.a).toleft(v - u) > 0) return false;
            if (edge.is_on(s.b) == 1 && (s.b - s.a).toleft(v - u) < 0) return false;
        }
    }
    return true;
}

