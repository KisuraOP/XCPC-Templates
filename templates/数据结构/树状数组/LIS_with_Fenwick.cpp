// f[i]/g[i] 以 i 结尾的 LIS 的长度/方案数。

using P = array<int, 2>;
P merge(P x, P y) {
	if (x[0] != y[0]) {
		return x[0] > y[0] ? x : y;
	}
	return {x[0], (x[1] + y[1]) % mod};
}

struct Fenwick {
	int n;
	vector<P> tr;
	Fenwick(int n) { 
		this->n = n;
		tr.assign(n + 1, P {0, 0});
	}
	void add(int pos, P x) {
		for (int i = pos; i <= n; i += i & -i) {
			tr[i] = merge(tr[i], x);
		}
	}
	P sum(int pos) {
		P res {0, 0};
		for (int i = pos; i > 0; i -= i & -i) {
			res = merge(res, tr[i]);
		}
		return res;
	}
};

// in main()
vector<int> f(n + 1), g(n + 1);
Fenwick fen(n + 1);
for (int i = 1; i <= n; i++) {
	auto [nf, ng] = fen.sum(a[i] - 1);
	f[i] = nf + 1;
	g[i] = (f[i] == 1 ? 1 : ng);
	fen.add(a[i], {f[i], g[i]});
}