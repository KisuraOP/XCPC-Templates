/*
依赖数据结构章节“树链剖分”中的 LLD.cpp。

level_ancestor G(adj, rt);
G.query(x, k) 返回 x 的 k 级祖先，若不存在则返回 0。

预处理时间复杂度 O(n log n)，查询时间复杂度 O(1)。
*/
struct level_ancestor : LLD {
    vector<vector<int>> f;
    vector<int> up;
    level_ancestor(vector<vector<int>> &adj, int rt) : LLD(adj, rt), f(__lg(n) + 1, vector<int>(n + 1)), up(n + 1) {
        f[0] = fa;
        for (int i = 1; i < f.size(); i++) {
            for (int x = 1; x <= n; x++) {
                f[i][x] = f[i - 1][f[i - 1][x]];
            }
        }
        for (int x = 1; x <= n; x++) {
            if (top[x] == x) {
                for (int i = 0, y = x; i < len[x]; i++) {
                    up[dfn[x] + i] = y;
                    y = fa[y];
                }
            }
        }
    }
    int query(int x, int k) {
        if (k >= dep[x]) {
            return 0;
        }
        if (!k) {
            return x;
        }
        int i = __lg(k);
        x = f[i][x];
        k -= 1LL << i;
        k -= dep[x] - dep[top[x]];
        x = top[x];
        return k < 0 ? rev[dfn[x] - k] : up[dfn[x] + k];
    }
};
