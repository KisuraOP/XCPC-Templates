vector<int> s(n + 1), ans(n + 1);
auto dfs1 = [&](auto &&self, int x, int p) -> void {
    s[x] = a[x];
    for (auto [y, w] : adj[x]) {
        if (y != p) {
            self(self, y, x);
            s[x] += s[y];
            ans[x] += ans[y] + s[y] * w;
        }
    }
};
auto dfs2 = [&](auto &&self, int x, int p) -> void {
    for (auto [y, w] : adj[x]) {
        if (y != p) {
            ans[y] = ans[x] + (s[rt] - 2 * s[y]) * w;
            self(self, y, x);
        }
    }
};
dfs1(dfs1, rt, 0);
dfs2(dfs2, rt, 0);
