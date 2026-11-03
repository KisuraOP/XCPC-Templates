// 依赖 Geometry_Rabbit_Base.cpp。
// 计算射线与直线的交点
// bool 表示是否存在交点, Point 为交点坐标。
// 若共线，返回射线原点。 若平行无交点，bool 为 false。
pair<bool, Point> ray_line_inter(const Ray &r, const Line &l)
{
    T crs = r.v ^ l.v;
    if (crs != 0) // 射线与直线不平行
    {
        Point res = l.inter({r.p, r.v});
        if (res == r.p || (res - r.p) * r.v >= 0) return {true, res};
        return {false, {}}; // 交点在射线的反方向延长线上
    }
    if (l.dis(r.p) <= eps) return {true, r.p};
    return {false, {}};
}

// 计算射线与线段的交点
// bool 表示是否存在交点, Point 为交点坐标。
// 若共线且有重合，返回离射线原点最近的交点。
pair<bool, Point> ray_seg_inter(const Ray &r, const Segment &s)
{
    const Line seg = {s.a, s.b - s.a};
    if ((r.v ^ seg.v) == 0) // 射线与线段平行
    {
        if (s.is_on(r.p) != 0) return {true, r.p};
        bool s_a_on_ray = (r.is_on(s.a) != 0);
        bool s_b_on_ray = (r.is_on(s.b) != 0);
        if (s_a_on_ray && s_b_on_ray) return {true, r.p.dis2(s.a) < r.p.dis2(s.b) ? s.a : s.b};
        if (s_a_on_ray) return {true, s.a};
        if (s_b_on_ray) return {true, s.b};
        return {false, {}};
    }
    auto res = ray_line_inter(r, seg);
    if (res.first && s.is_on(res.second) != 0) return {true, res.second};
    return {false, {}};
}

