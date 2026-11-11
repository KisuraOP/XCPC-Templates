vector<array<int, 2>> ans(n + 1);
auto dfs1 = [&](auto &&self, int x, int p) -> void {
    ans[x] = {0, a[x]};
    for (int y : adj[x]) {
        if (y != p) {
            self(self, y, x);
            ans[x][0] += max(ans[y][0], ans[y][1]);
            ans[x][1] += ans[y][0];
        }
    }
};
auto dfs2 = [&](auto &&self, int x, int p) -> void {
    for (int y : adj[x]) {
        if (y != p) {
            auto s = ans[x];
            s[0] -= max(ans[y][0], ans[y][1]);
            s[1] -= ans[y][0];
            ans[y][0] += max(s[0], s[1]);
            ans[y][1] += s[0];
            self(self, y, x);
        }
    }
};
dfs1(dfs1, rt, 0);
dfs2(dfs2, rt, 0);
