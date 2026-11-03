/*
LCT t(n);

t.link(x, y);
连边，两点已连通时返回 false。

t.cut(x, y);
删边，边不存在时返回 false。

t.same(x, y);
判断 x 和 y 是否连通。

以上操作均摊 O(log n)。
*/
struct LCT {
	struct Node {
		int ch[2] = {}, fa = 0, rev = 0;
	};
	vector<Node> a;
	vector<int> st;
	LCT(int n) : a(n + 1), st(n + 1) {}
	bool isrt(int x) {
		int f = a[x].fa;
		return a[f].ch[0] != x && a[f].ch[1] != x;
	}
	void flip(int x) {
		if (x) {
			swap(a[x].ch[0], a[x].ch[1]);
			a[x].rev ^= 1;
		}
	}
	void down(int x) {
		if (a[x].rev) {
			flip(a[x].ch[0]);
			flip(a[x].ch[1]);
			a[x].rev = 0;
		}
	}
	void rot(int x) {
		int y = a[x].fa, z = a[y].fa;
		int d = a[y].ch[1] == x, b = a[x].ch[d ^ 1];
		if (!isrt(y)) {
			a[z].ch[a[z].ch[1] == y] = x;
		}
		a[x].fa = z;
		a[y].ch[d] = b;
		if (b) {
			a[b].fa = y;
		}
		a[x].ch[d ^ 1] = y;
		a[y].fa = x;
	}
	void splay(int x) {
		int top = 0;
		st[0] = x;
		for (int y = x; !isrt(y); y = a[y].fa) {
			st[++top] = a[y].fa;
		}
		while (top >= 0) {
			down(st[top--]);
		}
		while (!isrt(x)) {
			int y = a[x].fa, z = a[y].fa;
			if (!isrt(y)) {
				rot((a[y].ch[0] == x) == (a[z].ch[0] == y) ? y : x);
			}
			rot(x);
		}
	}
	void access(int x) {
		int y = 0;
		for (int z = x; z; z = a[z].fa) {
			splay(z);
			a[z].ch[1] = y;
			y = z;
		}
		splay(x);
	}
	void make(int x) {
		access(x);
		flip(x);
	}
	int root(int x) {
		access(x);
		down(x);
		while (a[x].ch[0]) {
			x = a[x].ch[0];
			down(x);
		}
		splay(x);
		return x;
	}
	bool same(int x, int y) {
		return root(x) == root(y);
	}
	bool link(int x, int y) {
		make(x);
		if (root(y) == x) {
			return false;
		}
		a[x].fa = y;
		return true;
	}
	bool cut(int x, int y) {
		make(x);
		access(y);
		if (a[y].ch[0] != x || a[x].ch[1]) {
			return false;
		}
		a[y].ch[0] = a[x].fa = 0;
		return true;
	}
};
