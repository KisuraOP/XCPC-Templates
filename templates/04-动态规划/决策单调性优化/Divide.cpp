/*
auto f = divide(n, m, w);
f[i] 为前 i 项恰好分成 m 个非空连续段的最小费用。
w(l, r) 为区间 [l, r] 分成一组的费用；i < m 时 f[i] = inf。

组数固定时，要求最优分割点随前缀长度单调不减；费用相同时取最大的 k。
*/
template<class W>
vector<int> divide(int n, int m, W w) {
    vector<int> f(n + 1, inf), g = f;
    f[0] = 0;
    for (int t = 1; t <= m; t++) {
        swap(f, g);
        fill(f.begin(), f.end(), inf);
        auto dfs = [&](auto &&self, int l, int r, int ql, int qr) -> void {
            if (l > r) {
                return;
            }
            int mid = (l + r) / 2, p = ql;
            for (int k = ql; k <= min(qr, mid - 1); k++) {
                if (g[k] == inf) {
                    continue;
                }
                int v = g[k] + w(k + 1, mid);
                if (v <= f[mid]) {
                    f[mid] = v;
                    p = k;
                }
            }
            self(self, l, mid - 1, ql, p);
            self(self, mid + 1, r, p, qr);
        };
        dfs(dfs, t, n, t - 1, n - 1);
    }
    return f;
}
