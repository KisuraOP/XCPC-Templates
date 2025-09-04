struct DSU {
	vector<int> f, siz;
	DSU() {}
	DSU(int n) {
		f.resize(n + 1);
		siz.resize(n + 1);
		for(int i = 0; i <= n; i++) {
			f[i] = i;
			siz[i] = 1;
		}
	}
	int find(int x) {
		if (x == f[x]) {
			return x;
		}
		return f[x] = find(f[x]);
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	bool merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) {
			return false;
		}
		if (siz[x] < siz[y]) {
			swap(x, y);
		}
		siz[x] += siz[y];
		f[y] = x;
		return true;
	}
	int size(int x) {
		return siz[find(x)];
	}
};