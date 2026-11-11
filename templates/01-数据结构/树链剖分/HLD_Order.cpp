/*
依赖 HLD.cpp、HLD_Ext.cpp 中的 walk，以及“线段树”中的
SegTree_Packaged.cpp。

a[x] = {p, q} 表示点 x 上的函数 p * v + q，运算对 mod 取模。
query(x, y, v) 返回从 x 到 y 依次应用这些函数后的值。
Info.f 和 Info.g 分别保存区间正序、倒序的复合函数。

修改 a[x] 后调用 seg.modify(h.dfn[x], {a[x], a[x]})。

单点修改 O(log n)，路径查询 O(log^2 n)。
*/
struct Info {
    array<int, 2> f{1, 0}, g{1, 0};
    Info operator+(const Info &b) const {
        return {{f[0] * b.f[0] % mod, (f[1] * b.f[0] + b.f[1]) % mod},
                {b.g[0] * g[0] % mod, (b.g[1] * g[0] + g[1]) % mod}};
    }
};
HLD h(adj, rt);
vector<Info> b(n + 1);
for (int x = 1; x <= n; x++) {
    b[h.dfn[x]] = {a[x], a[x]};
}
SegmentTree<Info> seg(b);
auto query = [&](int x, int y, int v) {
    h.walk(x, y, [&](int l, int r, bool rev) {
        auto s = seg.query(l, r);
        auto t = rev ? s.g : s.f;
        v = (t[0] * v + t[1]) % mod;
    });
    return v;
};
