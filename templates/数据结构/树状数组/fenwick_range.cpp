/*
Fenwick fen(n);
创建。

fen.add(x, v);
单点 x 的值 +v。

fen.add(l, r, v);
区间 [l, r] 的值 +v。

int res = fen.sum(x);
求单点 x 的值。

int res = fen.sum(l, r);
求区间 [l, r] 的和。
*/

struct Fenwick {
	vector<int> f1, f2;
	int n;
	Fenwick(int n) : n(n + 1), f1(n + 1), f2(n + 1) {}
	void modify(int x, int v) {
		for (int i = x; i < n; i |= i + 1) {
			f1[i] += v;
			f2[i] += v * x;
		}
	}
	int get(int x) {
		int v = 0;
		for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
			v += f1[i] * (x + 1) - f2[i];
		}
		return v;
	}
	void add(int x, int v) {
		modify(x, v);
		modify(x + 1, -v);
	}
	void add(int l, int r, int v) {
		modify(l, v);
		modify(r + 1, -v);
	}
	int sum(int x) {
		return get(x) - get(x - 1);
	}
	int sum(int l, int r) {
		return get(r) - get(l - 1);
	}
};