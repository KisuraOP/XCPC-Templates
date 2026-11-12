/*
依赖 Centroid.cpp。

CTree t(n);

t.build();
加完边后建立点分树。

t.path(x, f);
按点分树根到 x 的顺序，对路径上的每个点 p 调用 f(p, d, q)。
d 是原树中 x 到 p 的距离。
q 是点分树中 p 到 x 路径上的下一个点，p = x 时 q = 0。
距离和示例用 q 扣除同一子树内重复统计的部分。

建树时间复杂度 O(n log n)。
path 时间复杂度 O(log n)，不含 f 的开销。
*/
struct CTree : Centroid {
	vector<int> par;
	vector<vector<array<int, 2>>> anc;
	CTree(int n) : Centroid(n), par(n + 1), anc(n + 1) {}
	void build(int x = 1) {
		Centroid::build([&](int x, int p) {
			par[x] = p;
			walk(x, 0, 0, [&](int y, int d) {
				anc[y].push_back({x, d});
			});
		}, x);
	}
	template<class F>
	void path(int x, F &&f) {
		for (int i = 0; i < anc[x].size(); i++) {
			auto [p, d] = anc[x][i];
			int q = i + 1 < anc[x].size() ? anc[x][i + 1][0] : 0;
			f(p, d, q);
		}
	}
};
