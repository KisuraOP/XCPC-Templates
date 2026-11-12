/*
LLD t(adj, rt);

dep[x] 是 x 的深度，len[x] 是从 x 向下的最长链的节点数。
son[x] 是 len 最大的儿子，top[x] 是所在长链的链顶。
dfn[x] 是优先遍历 son[x] 得到的 DFS 序，rev[i] 是第 i 个访问的点。
从 x 沿 son 向下的链对应 [dfn[x], dfn[x] + len[x] - 1]。

k 级祖先查询见树论章节的 Level_Ancestor.cpp。

预处理时间复杂度 O(n)。
*/
struct LLD {
    int n, tim = 0;
    vector<vector<int>> adj;
    vector<int> fa, dep, len, son, top, dfn, rev;
    LLD(vector<vector<int>> &adj, int rt) : n(adj.size() - 1), adj(adj), fa(n + 1), dep(n + 1), len(n + 1), son(n + 1), top(n + 1), dfn(n + 1), rev(n + 1) {
        dfs1(rt, 0);
        dfs2(rt, rt);
    }
    void dfs1(int x, int p) {
        fa[x] = p;
        dep[x] = dep[p] + 1;
        for (int y : adj[x]) {
            if (y != p) {
                dfs1(y, x);
                if (len[y] > len[son[x]]) {
                    son[x] = y;
                }
            }
        }
        len[x] = len[son[x]] + 1;
    }
    void dfs2(int x, int t) {
        top[x] = t;
        dfn[x] = ++tim;
        rev[tim] = x;
        if (son[x]) {
            dfs2(son[x], t);
        }
        for (int y : adj[x]) {
            if (y != fa[x] && y != son[x]) {
                dfs2(y, y);
            }
        }
    }
};
