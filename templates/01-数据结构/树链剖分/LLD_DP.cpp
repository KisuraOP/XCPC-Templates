LLD t(adj, rt);
vector<int> f(n + 1), ans(n + 1);
auto dfs = [&](auto &&self, int x) -> void {
    if (t.son[x]) {
        self(self, t.son[x]);
        ans[x] = ans[t.son[x]] + 1;
    }
    int p = t.dfn[x];
    f[p] = 1;
    for (int y : adj[x]) {
        if (y != t.fa[x] && y != t.son[x]) {
            self(self, y);
            for (int i = 0; i < t.len[y]; i++) {
                int d = i + 1;
                f[p + d] += f[t.dfn[y] + i];
                if (f[p + d] > f[p + ans[x]] || (f[p + d] == f[p + ans[x]] && d < ans[x])) {
                    ans[x] = d;
                }
            }
        }
    }
    if (f[p + ans[x]] == 1) {
        ans[x] = 0;
    }
};
dfs(dfs, rt);
