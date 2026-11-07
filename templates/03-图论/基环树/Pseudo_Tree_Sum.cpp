/*
依赖 Pseudo_Tree.cpp，先调用 g.work()，边权非负。

vector<int> ans = sumdis(g);
ans[x] 是 x 到同一连通块内所有点的最短路长度之和。
时间复杂度 O(n)。
*/
vector<int> sumdis(PseudoTree &g) {
	vector<int> sz(g.n + 1, 1), sub(g.n + 1), ans(g.n + 1), cnt(g.cir.size());
	for (int x : g.ord) {
		int y = g.fa[x];
		sz[y] += sz[x];
		sub[y] += sub[x] + sz[x] * g.e[g.pe[x]][2];
	}
	for (int c = 1; c < g.cir.size(); c++) {
		int k = g.cir[c].size() - 1, len = 0, tot = 0;
		vector<int> d(2 * k + 1), s(2 * k + 1), t(2 * k + 1);
		for (int i = 1; i <= k; i++) {
			int x = g.cir[c][i];
			cnt[c] += sz[x];
			tot += sub[x];
			len += g.e[g.ce[c][i]][2];
		}
		for (int i = 1; i <= 2 * k; i++) {
			int x = g.cir[c][(i - 1) % k + 1];
			if (i > 1) {
				d[i] = d[i - 1] + g.e[g.ce[c][(i - 2) % k + 1]][2];
			}
			s[i] = s[i - 1] + sz[x];
			t[i] = t[i - 1] + sz[x] * d[i];
		}
		for (int i = 1, j = 1; i <= k; i++) {
			j = max(j, i);
			while (j + 1 < i + k && d[j + 1] - d[i] <= len / 2) {
				j++;
			}
			int a = s[j] - s[i - 1], b = s[i + k - 1] - s[j];
			ans[g.cir[c][i]] = tot + t[j] - t[i - 1] - d[i] * a;
			ans[g.cir[c][i]] += (len + d[i]) * b - t[i + k - 1] + t[j];
		}
	}
	for (int i = g.ord.size(); i--;) {
		int x = g.ord[i], y = g.fa[x];
		ans[x] = ans[y] + g.e[g.pe[x]][2] * (cnt[g.id[x]] - 2 * sz[x]);
	}
	return ans;
}
