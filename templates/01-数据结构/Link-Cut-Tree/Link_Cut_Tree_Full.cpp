/*
维护森林中的点权，编号为 1 ~ n。

LCT t(v);
初始化点权为 v_i。
v 为 1-index。

以下操作均摊 O(log n)。

link(x, y) / cut(x, y) / same(x, y) 
连边 / 删边 / 判断连通。

make(x) 换根 / root(x) 返回当前树根。

set(x, w) 将点权赋为 w。
add(x, y, w) 将路径上的点权加 w。
query(x, y) 返回路径点权和。
kth(x, y, k) 返回从 x 到 y 的第 k 个点。
sub(r, x) 返回以 r 为根时 x 的子树点权和，包含 x。
lca(r, x, y) 返回以 r 为根时 x、y 的最近公共祖先。

路径、子树及 LCA 操作要求各点连通，k 从 1 开始且不超过路径点数。
*/
struct LCT {
	struct Node {
		int ch[2] = {}, fa = 0, sz = 1, rev = 0;
		int val = 0, sum = 0, tag = 0, vir = 0, all = 0;
	};
	vector<Node> a;
	vector<int> st;
	LCT(vector<int> &v) : a(v.size()), st(v.size()) {
		a[0].sz = 0;
		for (int i = 1; i < v.size(); i++) {
			a[i].val = a[i].sum = a[i].all = v[i];
		}
	}
	bool isrt(int x) {
		int f = a[x].fa;
		return a[f].ch[0] != x && a[f].ch[1] != x;
	}
	void up(int x) {
		int l = a[x].ch[0], r = a[x].ch[1];
		a[x].sz = a[l].sz + a[r].sz + 1;
		a[x].sum = a[l].sum + a[r].sum + a[x].val;
		a[x].all = a[l].all + a[r].all + a[x].val + a[x].vir;
	}
	void flip(int x) {
		if (x) {
			swap(a[x].ch[0], a[x].ch[1]);
			a[x].rev ^= 1;
		}
	}
	void apply(int x, int w) {
		if (x) {
			a[x].val += w;
			a[x].sum += w * a[x].sz;
			a[x].all += w * a[x].sz;
			a[x].tag += w;
		}
	}
	void down(int x) {
		if (a[x].rev) {
			flip(a[x].ch[0]);
			flip(a[x].ch[1]);
			a[x].rev = 0;
		}
		if (a[x].tag) {
			apply(a[x].ch[0], a[x].tag);
			apply(a[x].ch[1], a[x].tag);
			a[x].tag = 0;
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
		up(y);
		up(x);
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
	int access(int x) {
		int y = 0;
		for (int z = x; z; z = a[z].fa) {
			splay(z);
			a[z].vir += a[a[z].ch[1]].all - a[y].all;
			a[z].ch[1] = y;
			up(z);
			y = z;
		}
		splay(x);
		return y;
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
	void split(int x, int y) {
		make(x);
		access(y);
	}
	bool link(int x, int y) {
		make(x);
		if (root(y) == x) {
			return false;
		}
		access(y);
		a[x].fa = y;
		a[y].vir += a[x].all;
		up(y);
		return true;
	}
	bool cut(int x, int y) {
		split(x, y);
		if (a[y].ch[0] != x || a[x].ch[1]) {
			return false;
		}
		a[y].ch[0] = a[x].fa = 0;
		up(y);
		return true;
	}
	void set(int x, int w) {
		access(x);
		a[x].val = w;
		up(x);
	}
	void add(int x, int y, int w) {
		split(x, y);
		apply(y, w);
	}
	int query(int x, int y) {
		split(x, y);
		return a[y].sum;
	}
	int kth(int x, int y, int k) {
		split(x, y);
		while (true) {
			down(y);
			int l = a[y].ch[0];
			if (k == a[l].sz + 1) {
				splay(y);
				return y;
			}
			if (k <= a[l].sz) {
				y = l;
			} else {
				k -= a[l].sz + 1;
				y = a[y].ch[1];
			}
		}
	}
	int sub(int r, int x) {
		split(r, x);
		return a[x].val + a[x].vir;
	}
	int lca(int r, int x, int y) {
		make(r);
		access(x);
		return access(y);
	}
};
