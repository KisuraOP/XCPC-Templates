/*
查找图中是否有一个环，环上边权异或和为 0。
值存在 ok 中。
*/

struct DSU {
	vector<int> f, siz;
	vector<int> g;
	int cnt, ok;
	DSU() {}
	DSU(int n) {
		f.resize(n + 1);
		siz.resize(n + 1);
		g.resize(n + 1);
		for(int i = 0; i <= n; i++) {
			f[i] = i;
			siz[i] = 1;
		}
		cnt = n;
		ok = 1;
	}
	int find(int x) {
		if (x == f[x]) {
			return x;
		}
		int y = find(f[x]);
		g[x] ^= g[f[x]];
		return f[x] = y;
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	bool merge(int x, int y, int w) {
		if (same(x, y)) {
			if ((g[x] ^ g[y]) != w) {
				ok = 0;
			}
			return false;
		}
		int xx = x, yy = y;
		x = find(x);
		y = find(y);
		if (siz[x] < siz[y]) {
			swap(x, y);
		}
		siz[x] += siz[y];
		f[y] = x;
		g[y] = (g[xx] ^ g[yy] ^ w);
		cnt--;
		return true;
	}
	int size(int x) {
		return siz[find(x)];
	}
};