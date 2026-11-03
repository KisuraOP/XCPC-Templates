// 依赖 Geometry_Rabbit_Polygon.cpp。
// 两个三角形是否严格相交（相交区域面积 > 0）
bool triangle_cross(const Convex &A, const Convex &B) {
    for (int k = 0; k < 2; k++) {
        const auto &p = k ? A.p : B.p, &q = k ? B.p : A.p;
        for (int i = 0; i < 3; i++) {
            bool ok = false;
            for (int j = 0; j < 3; j++)
                ok |= (p[(i + 1) % 3] - p[i]).toleft(q[j] - p[i]) > 0;
            if (!ok) return false;
        }
    }
    return true;
}
