/*
依赖 Pseudo_Tree.cpp，先调用 g.work()。

PseudoLCA t(g);
t.lca(x, y) 返回同一棵树中两点的 LCA。
t.lift(x, k) 返回 x 的第 k 级祖先，若 k > g.dep[x] 则返回 0。

预处理时间复杂度 O(n log n)，查询时间复杂度 O(log n)。
*/
struct PseudoLCA {
	PseudoTree &g;
	vector<vector<int>> up;
	PseudoLCA(PseudoTree &g) : g(g), up(__lg(g.n) + 1, vector<int>(g.n + 1)) {
		up[0] = g.fa;
		for (int i = 1; i < up.size(); i++) {
			for (int x = 1; x <= g.n; x++) {
				up[i][x] = up[i - 1][up[i - 1][x]];
			}
		}
	}
	int lift(int x, int k) {
		if (k > g.dep[x]) {
			return 0;
		}
		for (int i = 0; k; i++, k >>= 1) {
			if (k & 1) {
				x = up[i][x];
			}
		}
		return x;
	}
	int lca(int x, int y) {
		if (g.dep[x] < g.dep[y]) {
			swap(x, y);
		}
		x = lift(x, g.dep[x] - g.dep[y]);
		if (x == y) {
			return x;
		}
		for (int i = up.size(); i--;) {
			if (up[i][x] != up[i][y]) {
				x = up[i][x];
				y = up[i][y];
			}
		}
		return g.fa[x];
	}
};
