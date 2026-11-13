/*
auto [cost, seq] = hamil(a, s, t);
a 为有向边权矩阵，无边填 inf，无向图填对称矩阵，允许负权。
求恰好经过每个顶点一次的最短路径，seq 按顺序保存顶点。
s、t 为起终点，0 表示不限；若无解则返回 {inf, {}}。
时间复杂度 O(n^2 2^n)。
*/
pair<int, vector<int>> hamil(const vector<vector<int>> &a, int s = 0, int t = 0) {
    int n = a.size() - 1, m = 1 << n;
    vector<vector<int>> f(m, vector<int>(n + 1, inf));
    for (int i = 1; i <= n; i++) {
        if (!s || i == s) {
            f[1 << (i - 1)][i] = 0;
        }
    }
    for (int S = 1; S < m; S++) {
        for (int x = 1; x <= n; x++) {
            if (f[S][x] == inf) {
                continue;
            }
            for (int y = 1; y <= n; y++) {
                if (!(S >> (y - 1) & 1) && a[x][y] != inf) {
                    int T = S | 1 << (y - 1);
                    f[T][y] = min(f[T][y], f[S][x] + a[x][y]);
                }
            }
        }
    }
    int x = t;
    for (int i = 1; !t && i <= n; i++) {
        if (f[m - 1][i] < f[m - 1][x]) {
            x = i;
        }
    }
    int ans = f[m - 1][x];
    if (ans == inf) {
        return {inf, {}};
    }
    vector<int> seq(n + 1);
    for (int i = n, S = m - 1; i; i--) {
        seq[i] = x;
        int T = S ^ 1 << (x - 1);
        for (int y = 1; T && y <= n; y++) {
            if (f[T][y] != inf && a[y][x] != inf && f[T][y] + a[y][x] == f[S][x]) {
                x = y;
                break;
            }
        }
        S = T;
    }
    return {ans, seq};
}
