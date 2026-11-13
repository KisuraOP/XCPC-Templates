/*
依赖 Bigraph_Matching_HK.cpp。

auto ans = paths(adj);
原图为 DAG，求覆盖所有顶点的最少条点不相交路径，允许单点路径。
ans[i] 按顺序保存第 i 条路径的顶点，O(n+m sqrt n)。
*/
vector<vector<int>> paths(const vector<vector<int>> &adj) {
    int n = adj.size() - 1;
    HK g(n, n);
    for (int x = 1; x <= n; x++) {
        for (int y : adj[x]) {
            g.add(x, y);
        }
    }
    g.solve();
    vector<vector<int>> ans(1);
    for (int x = 1; x <= n; x++) {
        if (!g.mr[x]) {
            ans.push_back(vector<int>(1));
            for (int y = x; y; y = g.ml[y]) {
                ans.back().push_back(y);
            }
        }
    }
    return ans;
}
