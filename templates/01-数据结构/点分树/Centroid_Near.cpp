/*
依赖 Centroid_Tree.cpp，边权非负。

CNear t(n);
加完边后调用 t.build()，初始没有标记点。

t.flip(x);
切换点 x 的标记状态。

t.ask(x);
返回 x 到最近标记点的距离，若没有标记点则返回 -1。
若 x 已标记，则返回 0。

修改 O(log^2 n)，查询 O(log n)。
*/
struct CNear : CTree {
    vector<int> on;
    vector<multiset<int>> s;
    CNear(int n) : CTree(n), on(n + 1), s(n + 1) {}
    void flip(int x) {
        on[x] ^= 1;
        path(x, [&](int p, int d, int q) {
            if (on[x]) {
                s[p].insert(d);
            } else {
                s[p].erase(s[p].find(d));
            }
        });
    }
    int ask(int x) {
        int ans = inf;
        path(x, [&](int p, int d, int q) {
            if (!s[p].empty()) {
                ans = min(ans, d + *s[p].begin());
            }
        });
        return ans == inf ? -1 : ans;
    }
};
