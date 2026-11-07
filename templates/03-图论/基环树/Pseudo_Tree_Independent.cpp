/*
依赖 Pseudo_Tree.cpp，先调用 g.work()。

int ans = indep(g, a);
a[x] 是点权，返回最大权独立集的权值和，允许空集。
有自环的点不能选。时间复杂度 O(n)。
*/
int indep(PseudoTree &g, const vector<int> &a) {
	vector<array<int, 2>> f(g.n + 1);
	for (int x = 1; x <= g.n; x++) {
		f[x] = {0, a[x]};
	}
	for (int x : g.ord) {
		int y = g.fa[x];
		f[y][0] += max(f[x][0], f[x][1]);
		f[y][1] += f[x][0];
	}
	int ans = 0;
	for (int c = 1; c < g.cir.size(); c++) {
		auto &v = g.cir[c];
		int best = 0;
		for (int s = 0; s < 2; s++) {
			array<int, 2> dp{-inf, -inf};
			dp[s] = f[v[1]][s];
			for (int i = 2; i < v.size(); i++) {
				dp = {max(dp[0], dp[1]) + f[v[i]][0], dp[0] + f[v[i]][1]};
			}
			best = max(best, s ? dp[0] : max(dp[0], dp[1]));
		}
		ans += best;
	}
	return ans;
}
