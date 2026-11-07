/*
依赖 Pseudo_Tree.cpp，先调用 g.work()。

int ans = diam(g);
返回各连通块最长简单路径长度之和，允许空路径。
时间复杂度 O(n)。
*/
int diam(PseudoTree &g) {
	vector<int> mx(g.n + 1), ans(g.cir.size());
	for (int x : g.ord) {
		int y = g.fa[x], w = g.e[g.pe[x]][2], c = g.id[x];
		ans[c] = max(ans[c], mx[y] + mx[x] + w);
		mx[y] = max(mx[y], mx[x] + w);
	}
	for (int c = 1; c < g.cir.size(); c++) {
		int k = g.cir[c].size() - 1, s = 0;
		deque<array<int, 2>> q;
		for (int i = 1; i <= 2 * k; i++) {
			int x = g.cir[c][(i - 1) % k + 1];
			if (i > 1) {
				s += g.e[g.ce[c][(i - 2) % k + 1]][2];
			}
			while (!q.empty() && i - q.front()[0] >= k) {
				q.pop_front();
			}
			if (!q.empty()) {
				ans[c] = max(ans[c], mx[x] + s + q.front()[1]);
			}
			while (!q.empty() && q.back()[1] <= mx[x] - s) {
				q.pop_back();
			}
			q.push_back({i, mx[x] - s});
		}
	}
	return accumulate(ans.begin(), ans.end(), 0LL);
}
