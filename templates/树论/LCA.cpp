vector fa(n + 1, vector<int>(22, 0));
vector<int> dep(n + 1);
auto dfs = [&] (auto self, int x, int fath) -> void {
	fa[x][0] = fath;
	dep[x] = dep[fath] + 1;
	for (int i = 1; i <= __lg(dep[x]) + 1; i++) {
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	}
	for (auto y : adj[x]) {
		if (y != fath) {
			self(self, y, x);
		}
	}
};
auto LCA = [&] (int x, int y) {
	if (dep[x] < dep[y]) {
		swap(x, y);
	}
	while (dep[x] > dep[y]) {
		x = fa[x][__lg(dep[x] - dep[y])];
	}
	if (x == y) {
		return x;
	} 
	for (int i = __lg(dep[x]); i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
};