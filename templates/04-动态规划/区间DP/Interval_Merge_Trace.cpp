// seq 按执行顺序保存 {l, k, r}，表示合并 [l, k] 和 [k + 1, r]。
vector<array<int, 3>> seq;
auto dfs = [&](auto &&self, int l, int r) -> void {
    if (l < r) {
        int k = p[l][r];
        self(self, l, k);
        self(self, k + 1, r);
        seq.push_back({l, k, r});
    }
};
dfs(dfs, 1, n);
