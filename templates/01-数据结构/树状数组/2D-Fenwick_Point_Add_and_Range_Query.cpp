/*
Fenwick fen(n, m);

fen.add(x, y, v);
给坐标为 (x, y) 的点 +v。

int res = fen.sum(x1, y1, x2, y2);
返回矩形 [x1, x2] × [y1, y2] 内的元素和。
*/

struct Fenwick {
    vector<vector<int>> f;
    int n, m;
    Fenwick(int _n, int _m) : n(_n), m(_m) {
        f.assign(_n + 1, vector<int>(_m + 1));
    }
    void add(int x, int y, int v) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                f[i][j] += v;
            }
        }
    }
    int sum(int x, int y) {
        int res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                res += f[i][j];
            }
        }
        return res;
    }
    int sum(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }
};