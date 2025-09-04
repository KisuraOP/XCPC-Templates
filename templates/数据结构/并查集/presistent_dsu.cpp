// 万用撤销模板
vector<pair<int *, int>> stk;
auto doit = [&] (int &x, int y) {
	stk.push_back({&x, x});
	x = y;
};	
auto roll = [&] (int t) {
	while (stk.size() > t) {
		auto [x, y] = stk.back();
		stk.pop_back();
		*x = y;
	}
};

/*
DSU dsu(n);
其中 n 为并查集大小。

撤销操作：
    (记录当前版本 v) int v = dsu.ver.size();
    (回到版本 v) dsu.roll(v);

其余操作和普通并查集等同。
*/
struct DSU {
	vector<int> f, siz;
	vector<array<int, 3>> ver;
	DSU() {}
	DSU(int n) { init(n);}
	void init(int n) {
		f.resize(n + 2);
		iota(f.begin(), f.end(), 0);
		siz.assign(n + 2, 1);
	}
	int find(int x) {
		if (x == f[x]) return x;
		return find(f[x]);
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	bool merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) {
			swap(x, y);
		}
		ver.push_back({x, y, siz[x]});
		siz[x] += siz[y];
		f[y] = x;
		return true;
	}
	int size(int x) {
		return siz[find(x)];
	}
	void roll(int v) {
		while (ver.size() > v) {
			auto [x, y, szx] = ver.back();
			ver.pop_back();
			f[y] = y;
			siz[x] = szx;
		}
	}
};