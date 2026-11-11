using A = array<int, 3>;
vector<array<A, 3>> ans(n + 1);
auto add = [&](int x, A v) {
    for (auto &u : ans[x]) {
        if (!u[1] || v > u) {
            swap(u, v);
        }
    }
};
auto dfs1 = [&](auto &&self, int x, int p) -> void {
    add(x, {0, x, 0});
    for (auto [y, w] : adj[x]) {
        if (y != p) {
            self(self, y, x);
            auto v = ans[y][0];
            add(x, {v[0] + w, v[1], y});
        }
    }
};
auto dfs2 = [&](auto &&self, int x, int p) -> void {
    for (auto [y, w] : adj[x]) {
        if (y != p) {
            auto v = ans[x][ans[x][0][2] == y];
            add(y, {v[0] + w, v[1], x});
            self(self, y, x);
        }
    }
};
dfs1(dfs1, rt, 0);
dfs2(dfs2, rt, 0);
