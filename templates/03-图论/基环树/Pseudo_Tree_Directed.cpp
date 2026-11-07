/*
依赖 Pseudo_Tree_LCA.cpp，先调用 g.work()。
每条边按 addEdge(x, y) 的顺序定向为 x -> y。
底层无向图的每个连通块恰有一个环，边的方向任意。
以下查询只计算边数，不使用边权。

PseudoDir t(g);
t.dist(x, y) 返回从 x 到 y 的最少步数，不可达时返回 -1。
t.walk(x, y, k) 判断能否从 x 恰好走 k 步到 y，允许重复经过点和边。
t.cnt[x] 是从 x 可达的不同点数，包括 x。

每个点出度均为 1 时，还可调用 t.jump(x, k)，返回走 k 步后的点。
一般定向下终点可能不唯一，不能使用 jump。

预处理时间复杂度 O(n log n)，dist、walk、jump 时间复杂度 O(log n)。
*/
struct PseudoDir : PseudoLCA {
	vector<int> uc, dc, cnt;
	vector<vector<int>> pre;
	PseudoDir(PseudoTree &g) : PseudoLCA(g), uc(g.n + 1), dc(g.n + 1), cnt(g.n + 1), pre(g.cir.size()) {
		vector<int> sub(g.n + 1, 1);
		for (int x : g.ord) {
			if (g.e[g.pe[x]][0] == g.fa[x]) {
				sub[g.fa[x]] += sub[x];
			}
		}
		for (int c = 1; c < g.cir.size(); c++) {
			int k = g.cir[c].size() - 1;
			pre[c].resize(k + 1);
			for (int i = 1; i <= k; i++) {
				pre[c][i] = pre[c][i - 1] + (g.e[g.ce[c][i]][0] != g.cir[c][i]);
			}
			vector<int> b(3 * k + 1), s(3 * k + 1), l(3 * k + 2), r(3 * k + 2);
			for (int i = 1; i <= 3 * k; i++) {
				int j = (i - 1) % k + 1;
				b[i] = pre[c][j] == pre[c][j - 1];
				s[i] = s[i - 1] + sub[g.cir[c][j]];
			}
			for (int i = 3 * k; i; i--) {
				r[i] = b[i] ? r[i + 1] + 1 : 0;
			}
			for (int i = 2; i <= 3 * k; i++) {
				l[i] = b[i - 1] ? 0 : l[i - 1] + 1;
			}
			for (int i = 1; i <= k; i++) {
				int j = i + k;
				cnt[g.cir[c][i]] = l[j] + r[j] + 1 >= k ? s[k] : s[j + r[j]] - s[j - l[j] - 1];
			}
		}
		for (int i = g.ord.size(); i--;) {
			int x = g.ord[i], y = g.fa[x], b = g.e[g.pe[x]][0] == x;
			uc[x] = uc[y] + !b;
			dc[x] = dc[y] + b;
			cnt[x] = sub[x] + (b ? cnt[y] : 0);
		}
	}
	array<int, 2> ways(int x, int y) {
		if (g.id[x] != g.id[y]) {
			return {-1, -1};
		}
		if (g.rt[x] == g.rt[y]) {
			int z = lca(x, y);
			if (uc[x] != uc[z] || dc[y] != dc[z]) {
				return {-1, -1};
			}
			return {g.dep[x] + g.dep[y] - 2 * g.dep[z], -1};
		}
		if (uc[x] || dc[y]) {
			return {-1, -1};
		}
		int c = g.id[x], a = g.pos[g.rt[x]], b = g.pos[g.rt[y]];
		int k = g.cir[c].size() - 1, d = (b - a + k) % k;
		int t = pre[c][b - 1] - pre[c][a - 1];
		if (a > b) {
			t += pre[c][k];
		}
		int s = g.dep[x] + g.dep[y];
		return {t == 0 ? s + d : -1, pre[c][k] - t == k - d ? s + k - d : -1};
	}
	int dist(int x, int y) {
		auto [a, b] = ways(x, y);
		return a < 0 ? b : b < 0 ? a : min(a, b);
	}
	bool walk(int x, int y, int k) {
		auto v = ways(x, y);
		for (int d : v) {
			if (d == k) {
				return true;
			}
		}
		if (g.id[x] != g.id[y] || uc[x] || dc[y]) {
			return false;
		}
		int c = g.id[x], len = g.cir[c].size() - 1;
		if (pre[c][len] != 0 && pre[c][len] != len) {
			return false;
		}
		for (int d : v) {
			if (d >= 0 && k >= d && (k - d) % len == 0) {
				return true;
			}
		}
		return false;
	}
	int jump(int x, int k) {
		if (k < g.dep[x]) {
			return lift(x, k);
		}
		k -= g.dep[x];
		x = g.rt[x];
		int c = g.id[x], len = g.cir[c].size() - 1;
		if (pre[c][len]) {
			k = -k;
		}
		return g.cir[c][(g.pos[x] - 1 + k % len + len) % len + 1];
	}
};
