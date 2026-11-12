/*
依赖 Centroid_Tree.cpp。

CSum t(n);
初始点权为 0，加完边后调用 t.build()。

t.inc(x, v);
将点 x 的权值加 v。

t.ask(x);
将每个点的权值乘以该点到 x 的距离，返回总和。

修改、查询的时间复杂度均为 O(log n)。
*/
struct CSum : CTree {
	vector<int> cnt, sum, ds;
	CSum(int n) : CTree(n), cnt(n + 1), sum(n + 1), ds(n + 1) {}
	void inc(int x, int v) {
		path(x, [&](int p, int d, int q) {
			cnt[p] += v;
			sum[p] += v * d;
			if (q) {
				ds[q] += v * d;
			}
		});
	}
	int ask(int x) {
		int res = 0;
		path(x, [&](int p, int d, int q) {
			res += sum[p] + cnt[p] * d;
			if (q) {
				res -= ds[q] + cnt[q] * d;
			}
		});
		return res;
	}
};
