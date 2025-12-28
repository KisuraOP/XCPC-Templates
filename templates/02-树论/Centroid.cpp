int rt = 0;
vector<int> sz(n + 1), mx(n + 1);
mx[0] = inf;
auto getrt = [&] (auto self, int x, int f) -> void {
	sz[x] = 1;
	mx[x] = 0;
	for (auto y : adj[x]) {
		if (y == f) {
			continue;
		}
		self(self, y, x);
		sz[x] += sz[y];
		mx[x] = max(mx[x], sz[y]);
	}
	mx[x] = max(mx[x], n - sz[x]);
	if (mx[x] < mx[rt]) {
		rt = x;
	}
};
getrt(getrt, 1, 0);