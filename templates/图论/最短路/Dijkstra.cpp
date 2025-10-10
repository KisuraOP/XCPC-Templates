vector<int> dis(n + 1);
vector<int> vis(n + 1);
auto dijkstra = [&] (int S) {
	dis.assign(n + 1, inf);
	vis.assign(n + 1, false);

	#define P pair<int, int>
	priority_queue<P, vector<P>, greater<P>> Q;
	Q.push({0, S});
	dis[S] = 0;

	while (!Q.empty()) {
		auto [dist, x] = Q.top();
		Q.pop();
		if (vis[x]) {
			continue;
		}
		vis[x] = true;

		for (auto [y, w] : adj[x]) {
			if (dis[y] > dist + w) {
				dis[y] = dist + w;
				Q.push({dis[y], y});
			}
		}
	}
};