/*
依赖 LLD.cpp。

对每个点 x，求一个距离 d，使其子树中到 x 恰好有 d 条边的节点最多；
若有多个这样的距离，取最小值，存入 ans[x]。
总复杂度 O(n)。
*/
LLD t(adj, rt);
vector<int> f(n + 1), ans(n + 1);
auto dfs = [&](auto &&self, int x) -> void {
	if (t.son[x]) {
		self(self, t.son[x]);
		ans[x] = ans[t.son[x]] + 1;
	}
	int p = t.dfn[x];
	f[p] = 1;
	for (int y : adj[x]) {
		if (y != t.fa[x] && y != t.son[x]) {
			self(self, y);
			for (int i = 0; i < t.len[y]; i++) {
				int d = i + 1;
				f[p + d] += f[t.dfn[y] + i];
				if (f[p + d] > f[p + ans[x]] || (f[p + d] == f[p + ans[x]] && d < ans[x])) {
					ans[x] = d;
				}
			}
		}
	}
	if (f[p + ans[x]] == 1) {
		ans[x] = 0;
	}
};
dfs(dfs, rt);
