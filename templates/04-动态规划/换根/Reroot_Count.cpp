vector<int> f(n + 1, 1), ans(n + 1);
auto dfs1 = [&](auto &&self, int x, int p) -> void {
    for (int y : adj[x]) {
        if (y != p) {
            self(self, y, x);
            f[x] = f[x] * (f[y] + 1) % mod;
        }
    }
};
auto dfs2 = [&](auto &&self, int x, int fa, int p) -> void {
    ans[x] = f[x] * p % mod;
    int m = adj[x].size();
    vector<int> s(m + 1, 1);
    for (int i = m - 1; i >= 0; i--) {
        int y = adj[x][i];
        s[i] = s[i + 1] * (y == fa ? 1 : f[y] + 1) % mod;
    }
    for (int i = 0; i < m; i++) {
        int y = adj[x][i];
        if (y != fa) {
            self(self, y, x, (p * s[i + 1] + 1) % mod);
            p = p * (f[y] + 1) % mod;
        }
    }
};
dfs1(dfs1, rt, 0);
dfs2(dfs2, rt, 0, 1);
