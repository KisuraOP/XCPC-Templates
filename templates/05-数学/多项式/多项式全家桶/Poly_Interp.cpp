// 依赖 Poly_Mul.cpp、Poly_Base.cpp、Poly_Eval.cpp。
// ---------- 多项式快速插值 O(Nlog^2N) ----------

vector<int> solve_interp(int p, int l, int r, const vector<int> &V) {
    if (l == r) {
        return {V[l]};
    }
    int mid = (l + r) >> 1;
    auto L_ans = solve_interp(p << 1, l, mid, V);
    auto R_ans = solve_interp(p << 1 | 1, mid + 1, r, V);
    return (L_ans * ptr[p << 1 | 1]) + (R_ans * ptr[p << 1]);
}
vector<int> poly_interpolate(const vector<array<int, 2>> &p) {
    int n = p.size();
    if (n == 0) {
        return {};
    }
    if (n == 1) {
        return {(p[0][1] % mod + mod) % mod};
    }
    vector<int> X(n), Y(n);
    for (int i = 0; i < n; ++i) {
        X[i] = (p[i][0] % mod + mod) % mod;
        Y[i] = (p[i][1] % mod + mod) % mod;
    }
    ptr.assign(4 * n, {});
    build_ptr(1, 0, n - 1, X);
    vector<int> F = poly_deriv(ptr[1]);
    vector<int> G(n), V(n);
    calc_ptr(F, 1, 0, n - 1, X, G);
    for (int i = 0; i < n; ++i) {
        int inv = qpow(G[i], mod - 2);
        V[i] = Y[i] * inv % mod;
    }
    auto res = solve_interp(1, 0, n - 1, V);
    res.resize(n, 0); 
    return res;
}
