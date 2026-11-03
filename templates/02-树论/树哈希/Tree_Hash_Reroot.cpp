// 依赖 Tree_Hash.cpp。
// g[x]: 将 (x, fa[x]) 切断后，以 fa[x] 为根的子树的哈希值
vector<ull> g(n + 1), s(n + 1);
auto dfs2 = [&] (auto self, int x, int fa) -> void {
	if (fa > 0) {
		s[x] += shift(g[x]);
	}
	for (auto y : adj[x]) {
		if (y != fa) {
			s[x] += shift(f[y]);
		}
	}
	for (auto y : adj[x]) {
		if (y != fa) {
			g[y] = 1 + (s[x] - shift(f[y]));
			self(self, y, x);
		}
	}
}; 
dfs2(dfs2, 1, 0);
