/*
找到三角剖分里的所有三角形，
并为每条有向线段找到逆时针方向的三角形顶点编号。
*/
vector<vector<int>> adj(n + 1);
auto Add = [&] (int x, int y) {
    if (x > y) {
        swap(x, y);
    }
    adj[x].push_back(y);
    adj[y].push_back(n + x);
}; 
for (int i = 1; i <= n; i++) {
    Add(i, i % n + 1);
}
vector<array<int, 2>> E;
for (int i = 0; i < n - 3; i++) {
    int x, y;
    cin >> x >> y;
    E.push_back({x, y});
    Add(x, y);
}
for (int x = 1; x <= n; x++) {
    sort(adj[x].begin(), adj[x].end());
    for (auto &y : adj[x]) {
        if (y > n) {
            y -= n;
        }
    }
}
for (int i = 1; i <= n; i++) {
    for (int j = 1; j < adj[i].size(); j++) {
        int x = adj[i][j - 1];
        int y = adj[i][j];
        pv[y][x] = i;
    }
}