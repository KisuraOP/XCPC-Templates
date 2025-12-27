/*
枚举三元环，O(m\sqrt{m})。
不会重复枚举。
*/
vector<int> deg(n + 1);
vector<array<int, 2>> E;
for (int i = 0; i < m; i++) {
	int x, y;
	cin >> x >> y;
	x++; y++;
	E.push_back({x, y});
	deg[x]++;
	deg[y]++;
}
vector<vector<int>> adj(n + 1);
for (auto [x, y] : E) {
	if (deg[x] > deg[y] || (deg[x] == deg[y] && x > y)) {
		swap(x, y);
	}
	adj[x].push_back(y);
}
vector<int> vis(n + 1);
for (int x = 1; x <= n; x++) {
	for (auto y : adj[x]) {
		vis[y] = x;
	}
	for (auto y : adj[x]) {
		for (auto z : adj[y]) {
			if (vis[z] == x) {
				// (x, y, z) is a triangle
				// do something
			}
		}
	}
}