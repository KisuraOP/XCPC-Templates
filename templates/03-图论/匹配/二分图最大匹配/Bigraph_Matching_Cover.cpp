/*
依赖 Bigraph_Matching_HK.cpp，先调用 g.solve()。

auto [l, r] = cover(g);
l[x]、r[y] 表示左右部顶点是否属于一组最小点覆盖。
取反即为一组最大独立集的选择标记。
恢复时间 O(V+E)，不改变匹配。
*/
array<vector<int>, 2> cover(const HK &g) {
    vector<int> l(g.ml.size()), r(g.mr.size()), q;
    for (int i = 1; i < l.size(); i++) {
        if (!g.ml[i]) {
            l[i] = 1;
            q.push_back(i);
        }
    }
    for (int i = 0; i < q.size(); i++) {
        int x = q[i];
        for (int j = g.adj[x][0]; j < g.adj[x][1]; j++) {
            int y = g.e[j];
            if (!r[y]) {
                r[y] = 1;
                if (int z = g.mr[y]) {
                    l[z] = 1;
                    q.push_back(z);
                }
            }
        }
    }
    for (int i = 1; i < l.size(); i++) {
        l[i] ^= 1;
    }
    return {l, r};
}
