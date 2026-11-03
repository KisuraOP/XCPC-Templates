// 依赖 Geometry_Jiangly_Base.cpp。
template<class T>
double area(vector<Point<T>> a) {
    int n = a.size();
    double res = 0;
    for (int i = 0; i < n; i++) {
        res += cross(a[i], a[(i + 1) % n]);
    }
    res = fabs(res);
    res /= 2;
    return res;
}
