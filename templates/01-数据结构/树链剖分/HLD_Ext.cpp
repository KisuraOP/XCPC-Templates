/*
依赖 HLD.cpp，以下成员按需放入 HLD 内。

h.kth(x, y, k) 返回从 x 到 y 的第 k 个点。
若路径不足 k 个点则返回 0。

h.sub(x, rt, f) 以 rt 为根，枚举 x 子树内各点对应的闭区间。
每个区间调用 f(l, r)，最多调用两次。

h.walk(x, y, f) 按从 x 到 y 的顺序调用 f(l, r, rev)。
l <= r；rev 为 true 时按 r 到 l 读取，否则按 l 到 r 读取。
h.walk(x, y, f, true) 用于边权，边权存到较深端点。

时间复杂度 O(log n)，不含回调开销。
*/
int kth(int x, int y, int k) {
    int z = LCA(x, y);
    int a = dep[x] - dep[z] + 1, b = dep[y] - dep[z];
    if (k > a + b) {
        return 0;
    }
    return k <= a ? jump(x, k - 1) : jump(y, a + b - k);
}
template<class F>
void sub(int x, int rt, F &&f) {
    if (x == rt) {
        f(1, n);
    } else if (dfn[rt] < dfn[x] || dfn[rt] >= dfn[x] + sz[x]) {
        f(dfn[x], dfn[x] + sz[x] - 1);
    } else {
        int y = jump(rt, dep[rt] - dep[x] - 1);
        f(1, dfn[y] - 1);
        if (dfn[y] + sz[y] <= n) {
            f(dfn[y] + sz[y], n);
        }
    }
}
template<class F>
void walk(int x, int y, F &&f, bool edge = false) {
    vector<array<int, 2>> a;
    while (top[x] != top[y]) {
        if (dep[top[x]] > dep[top[y]]) {
            f(dfn[top[x]], dfn[x], true);
            x = fa[top[x]];
        } else {
            a.push_back({dfn[top[y]], dfn[y]});
            y = fa[top[y]];
        }
    }
    bool dir = dep[x] > dep[y];
    if (dir) {
        swap(x, y);
    }
    if (dfn[x] + edge <= dfn[y]) {
        f(dfn[x] + edge, dfn[y], dir);
    }
    for (int i = a.size() - 1; i >= 0; i--) {
        f(a[i][0], a[i][1], false);
    }
}
