/*
依赖并查集中的 Presistent_DSU.cpp。

auto ans = dyncon(n, op);
op[i] = {1, x, y}：加入无向边，边编号为 i。
op[i] = {2, id, 0}：删除编号为 id 的边。
op[i] = {3, x, y}：查询 x、y 是否连通。
ans 按查询顺序保存 0 或 1，支持重边、自环。
*/
vector<int> dyncon(int n, const vector<array<int, 3>> &op) {
    int q = op.size() - 1;
    vector<vector<array<int, 2>>> tr(4 * q + 4);
    auto add = [&](auto self, int p, int l, int r, int L, int R, array<int, 2> e) -> void {
        if (L <= l && r <= R) {
            tr[p].push_back(e);
            return;
        }
        int mid = (l + r) / 2;
        if (L <= mid) {
            self(self, p * 2, l, mid, L, R, e);
        }
        if (R > mid) {
            self(self, p * 2 + 1, mid + 1, r, L, R, e);
        }
    };
    vector<int> end(q + 1, q), ans(1);
    for (int i = 1; i <= q; i++) {
        if (op[i][0] == 2) {
            end[op[i][1]] = i - 1;
        }
    }
    for (int i = 1; i <= q; i++) {
        if (op[i][0] == 1) {
            add(add, 1, 1, q, i, end[i], {op[i][1], op[i][2]});
        }
    }
    DSU dsu(n);
    auto calc = [&](auto self, int p, int l, int r) -> void {
        int v = dsu.ver.size();
        for (auto [x, y] : tr[p]) {
            dsu.merge(x, y);
        }
        if (l == r) {
            if (op[l][0] == 3) {
                ans.push_back(dsu.same(op[l][1], op[l][2]));
            }
        } else {
            int mid = (l + r) / 2;
            self(self, p * 2, l, mid);
            self(self, p * 2 + 1, mid + 1, r);
        }
        dsu.roll(v);
    };
    if (q) {
        calc(calc, 1, 1, q);
    }
    return ans;
}
