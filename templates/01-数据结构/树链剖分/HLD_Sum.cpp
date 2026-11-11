/*
依赖 HLD.cpp 和“线段树”中的 Lazy_SegTree_Packaged.cpp。

a[x] 为点权；用于边权时，存 x 与父亲之间的边权，并令 a[rt] = 0。

add(x, y, v) 将路径上各点的权值加 v，sum(x, y) 返回路径权值和。
subadd(x, v) 将子树内各点的权值加 v，subsum(x) 返回子树权值和。
以上调用的最后一个参数传 true 时，改为操作边权。

路径操作 O(log^2 n)，子树操作 O(log n)。
*/
struct Tag {
    int add = 0;
    void apply(const Tag &t) {
        add += t.add;
    }
};
struct Info {
    int sum = 0, len = 1;
    void apply(const Tag &t) {
        sum += t.add * len;
    }
    Info operator+(const Info &b) const {
        return {sum + b.sum, len + b.len};
    }
};
HLD h(adj, rt);
vector<Info> b(n + 1);
for (int x = 1; x <= n; x++) {
    b[h.dfn[x]] = {a[x], 1};
}
LazySegmentTree<Info, Tag> seg(b);
auto add = [&](int x, int y, int v, bool edge = false) {
    h.path(x, y, [&](int l, int r) {
        seg.modify(l, r, {v});
    }, edge);
};
auto sum = [&](int x, int y, bool edge = false) {
    int ans = 0;
    h.path(x, y, [&](int l, int r) {
        ans += seg.query(l, r).sum;
    }, edge);
    return ans;
};
auto subadd = [&](int x, int v, bool edge = false) {
    int l = h.dfn[x] + edge, r = h.dfn[x] + h.sz[x] - 1;
    if (l <= r) {
        seg.modify(l, r, {v});
    }
};
auto subsum = [&](int x, bool edge = false) {
    int l = h.dfn[x] + edge, r = h.dfn[x] + h.sz[x] - 1;
    return l <= r ? seg.query(l, r).sum : 0;
};
