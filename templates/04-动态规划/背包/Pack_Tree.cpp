/*
依赖 adj、w、v：adj 为无向树的邻接表，w、v 存重量和价值。

auto f = tree(rt, m);
树以 rt 为根，选择一个点必须同时选择其祖先。

f[j] 为恰好装满 j 的最大价值，无解时为 -inf。
时间复杂度 O(nm)。
*/
auto tree = [&](int rt, int m) {
    vector<int> a(1), r(adj.size());
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        int l = a.size();
        a.push_back(u);
        for (int x : adj[u]) {
            if (x != fa) {
                self(self, x, u);
            }
        }
        r[l] = a.size();
    };
    dfs(dfs, rt, 0);
    vector<vector<int>> f(a.size() + 1, vector<int>(m + 1, -inf));
    f.back()[0] = 0;
    for (int i = a.size() - 1; i > 0; i--) {
        int u = a[i];
        f[i] = f[r[i]];
        for (int j = w[u]; j <= m; j++) {
            if (f[i + 1][j - w[u]] != -inf) {
                f[i][j] = max(f[i][j], f[i + 1][j - w[u]] + v[u]);
            }
        }
    }
    return f[1];
};
