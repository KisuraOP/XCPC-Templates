// floyd 求无向图最小环
vector G(n + 1, vector<int>(n + 1, 1e12)), mp(G);
for (int i = 1; i <= n; i++) {
	G[i][i] = 0;
	mp[i][i] = 0;
}
for (int i = 0; i < m; i++) {
	int x, y, w;
	cin >> x >> y >> w;
	G[x][y] = G[y][x] = min(G[x][y], w);
	mp[x][y] = mp[y][x] = min(mp[x][y], w);
}
int ans = inf;
for (int k = 1; k <= n; k++) {
	for (int i = 1; i < k; i++) {
		for (int j = i + 1; j < k; j++) {
			ans = min(ans, G[i][j] + mp[i][k] + mp[k][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			G[i][j] = G[j][i] = min(G[i][j], G[i][k] + G[k][j]);
		}
	}
}