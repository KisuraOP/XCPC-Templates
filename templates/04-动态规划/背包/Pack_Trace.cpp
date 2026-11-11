/*
auto res = trace(w, v, m);
每件物品至多选一次，res.first 为总重量不超过 m 的最大价值，
res.second 为对应的一组物品编号，时间复杂度 O(nm)。
*/
pair<int, vector<int>> trace(const vector<int> &w, const vector<int> &v, int m) {
    int n = w.size() - 1;
    vector<vector<int>> f(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1];
        for (int j = w[i]; j <= m; j++) {
            f[i][j] = max(f[i][j], f[i - 1][j - w[i]] + v[i]);
        }
    }
    int ans = f[n][m];
    vector<int> a;
    for (int i = n; i >= 1; i--) {
        if (f[i][m] != f[i - 1][m]) {
            a.push_back(i);
            m -= w[i];
        }
    }
    reverse(a.begin(), a.end());
    return {ans, a};
}
