// 无向正权图全局最小割 O(n^3+m)
// 传 1-index 邻接表
int stoer_wagner(const vector<vector<array<int, 2>>> &adj) {
	int n = adj.size() - 1;
	vector g(n, vector<int>(n));
	for (int x = 1; x <= n; x++) {
		for (auto [y, w] : adj[x]) {
			g[x - 1][y - 1] += w;
		}
	}
	vector<int> v(n);
	iota(v.begin(), v.end(), 0);
	int ans = inf;
	while (v.size() > 1) {
		vector<int> w(n), vis(n);
		int s = -1, t = -1;
		for (int k = 0; k < v.size(); k++) {
			int x = -1;
			for (auto u : v) {
				if (!vis[u] && (x < 0 || w[u] > w[x])) {
					x = u;
				}
			}
			s = t;
			t = x;
			vis[x] = true;
			for (auto u : v) {
				if (!vis[u]) {
					w[u] += g[x][u];
				}
			}
		}
		ans = min(ans, w[t]);
		for (auto u : v) {
			if (u != t) {
				g[u][s] += g[t][u];
				g[s][u] = g[u][s];
			}
		}
		v.erase(find(v.begin(), v.end(), t));
	}
	return ans;
}