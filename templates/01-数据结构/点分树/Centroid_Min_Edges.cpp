/*
依赖 Centroid.cpp。

edges(t, k);
返回边权和恰好为 k 的路径的最少边数，两个端点不同。
若不存在则返回 -1。
加完边后直接调用，不要先调用 t.build。

时间复杂度 O(n log^2 n)。
*/
int edges(Centroid &t, int k) {
    int ans = inf;
    t.build([&](int x, int p) {
        map<int, int> f{{0, 0}};
        for (auto [y, w] : t.adj[x]) {
            if (t.del[y]) {
                continue;
            }
            vector<array<int, 2>> a;
            auto dfs = [&](auto &&self, int z, int fa, int d, int c) -> void {
                a.push_back({d, c});
                for (auto [v, w] : t.adj[z]) {
                    if (v != fa && !t.del[v]) {
                        self(self, v, z, d + w, c + 1);
                    }
                }
            };
            dfs(dfs, y, x, w, 1);
            for (auto [d, c] : a) {
                auto it = f.find(k - d);
                if (it != f.end()) {
                    ans = min(ans, c + it->second);
                }
            }
            for (auto [d, c] : a) {
                auto it = f.emplace(d, c).first;
                it->second = min(it->second, c);
            }
        }
    });
    return ans == inf ? -1 : ans;
}
