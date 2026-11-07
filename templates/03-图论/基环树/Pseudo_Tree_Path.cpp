/*
依赖 Pseudo_Tree_LCA.cpp，先调用 g.work()，边权非负。

PseudoPath t(g);
auto [mn, mx] = t.path(x, y);
返回 x 到 y 的最短路及最长简单路径长度，不连通时均为 -1。
x = y 时均为 0。

同一连通块中，g.rt[x] == g.rt[y] 当且仅当简单路径唯一。
预处理时间复杂度 O(n log n)，查询时间复杂度 O(log n)。
*/
struct PseudoPath : PseudoLCA {
	vector<vector<int>> pre;
	PseudoPath(PseudoTree &g) : PseudoLCA(g), pre(g.cir.size()) {
		for (int c = 1; c < g.cir.size(); c++) {
			pre[c].resize(g.cir[c].size());
			for (int i = 1; i < pre[c].size(); i++) {
				pre[c][i] = pre[c][i - 1] + g.e[g.ce[c][i]][2];
			}
		}
	}
	array<int, 2> path(int x, int y) {
		if (g.id[x] != g.id[y]) {
			return {-1, -1};
		}
		if (g.rt[x] == g.rt[y]) {
			int d = g.dis[x] + g.dis[y] - 2 * g.dis[lca(x, y)];
			return {d, d};
		}
		int c = g.id[x], a = g.pos[g.rt[x]], b = g.pos[g.rt[y]];
		int d = abs(pre[c][a - 1] - pre[c][b - 1]);
		int s = g.dis[x] + g.dis[y], t = pre[c].back() - d;
		return {s + min(d, t), s + max(d, t)};
	}
};
