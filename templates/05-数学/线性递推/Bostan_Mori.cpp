/*
依赖多项式中的 Poly_Mul.cpp。

bostan(p, q, n);
返回 [x^n] P(x)/Q(x)，p[i]、q[i] 为 x^i 的系数。
*/
int bostan(vector<int> p, vector<int> q, int n) {
    for (; n && !p.empty(); n >>= 1) {
        auto r = q;
        for (int i = 1; i < r.size(); i += 2) {
            r[i] = (mod - r[i]) % mod;
        }
        p = p * r;
        q = q * r;
        vector<int> a, b;
        for (int i = n & 1; i < p.size(); i += 2) {
            a.push_back(p[i]);
        }
        for (int i = 0; i < q.size(); i += 2) {
            b.push_back(q[i]);
        }
        p = move(a);
        q = move(b);
    }
    return p.empty() ? 0 : p[0] * qpow(q[0], mod - 2) % mod;
}
