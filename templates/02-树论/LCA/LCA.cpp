vector fa(22, vector<int>(n + 1));
vector<int> dep(n + 1);
auto dfs = [&] (auto self, int x, int f) -> void {
	fa[0][x] = f;
	dep[x] = dep[f] + 1;
	for (int i = 1; i <= __lg(dep[x]) + 1; i++) {
		fa[i][x] = fa[i - 1][fa[i - 1][x]];
	}
	for (auto y : adj[x]) {
		if (y != f) {
			self(self, y, x);
		}
	}
};
auto LCA = [&] (int x, int y) {
	if (dep[x] < dep[y]) {
		swap(x, y);
	}
	while (dep[x] > dep[y]) {
		x = fa[__lg(dep[x] - dep[y])][x];
	}
	if (x == y) {
		return x;
	} 
	for (int i = __lg(dep[x]); i >= 0; i--) {
		if (fa[i][x] != fa[i][y]) {
			x = fa[i][x];
			y = fa[i][y];
		}
	}
	return fa[0][x];
};