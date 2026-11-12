/*
依赖 Geometry_Rabbit_Circle.cpp。

Circle c = mincir(p);
返回覆盖所有点的最小圆，c.c 为圆心，c.r 为半径。
空点集返回圆心为原点、半径为 0 的圆。
随机增量法，期望时间复杂度 O(n)。
*/
Circle mincir(vector<Point> p) {
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(p.begin() + 1, p.end(), rng);
    auto diam = [&](Point a, Point b) {
        return Circle{(a + b) / 2, a.dis(b) / 2};
    };
    auto circ = [&](Point a, Point b, Point c) {
        Point u = b - a, v = c - a;
        T z = 2 * (u ^ v);
        if (z == 0) {
            Circle q = diam(a, b);
            for (auto w : {diam(a, c), diam(b, c)}) {
                if (w.r > q.r) {
                    q = w;
                }
            }
            return q;
        }
        Point o = a + Point{v.y * u.len2() - u.y * v.len2(),
            u.x * v.len2() - v.x * u.len2()} / z;
        return Circle{o, o.dis(a)};
    };
    Circle c{p.size() > 1 ? p[1] : Point{0, 0}, 0};
    auto out = [&](Point a) {
        return a.dis(c.c) > c.r + eps;
    };
    for (int i = 1; i < p.size(); i++) {
        if (!out(p[i])) {
            continue;
        }
        c = {p[i], 0};
        for (int j = 1; j < i; j++) {
            if (!out(p[j])) {
                continue;
            }
            c = diam(p[i], p[j]);
            for (int k = 1; k < j; k++) {
                if (out(p[k])) {
                    c = circ(p[i], p[j], p[k]);
                }
            }
        }
    }
    return c;
}
