struct DynamicCactus {
	int n, m;
	struct tree {
		bool ring, edge, sqr, rev;
		int fa, son[2], val, sum;
		tree(const int &w = 0, const bool &f = 0, const bool &g = 0): 
			fa(0), rev(0), val(w), sum(w), ring(f), sqr(f), edge(g) {
			son[0] = son[1] = 0;
		}
		const void reverse() {
			rev ^= 1;
			swap(son[0], son[1]);
		}
	};
	vector<tree> t;
	vector<int> recycle;
	int tail, top;

	DynamicCactus(int tn, int tm) {
		n = tn + 5;
		m = tm + 5;
		tail = top = 0;
		t.resize(n + 3 * m);
		recycle.resize(n + 3 * m);
		init();
	}
	
	const bool identity(int p) {
		return t[t[p].fa].son[1] == p;
	}
	
	const bool isroot(int p) {
		return t[t[p].fa].son[0] ^ p && t[t[p].fa].son[1] ^ p;
	}
	
	const bool isrothy(int p) {
		return isroot(p) || t[t[p].fa].sqr;
	}
	
	const void connect(int p, int fa, bool f) {
		if (p) {
			t[p].fa = fa;
		}
		if (fa) {
			t[fa].son[f] = p;
		}
	}
	const void pushup_Round(int p) {
		int l = t[p].son[0];
		int r = t[p].son[1];
		t[p].ring = t[l].ring || t[r].ring;
		t[p].sum = t[l].sum + t[p].val + t[r].sum;
	}
	const void pushup_Square(int p) {
		int l = t[p].son[0];
		int r = t[p].son[1];
		if (!l || !r) {
			t[p].sum = t[l | r].sum;
		} else {
			t[p].sum = min(t[l].sum, t[r].sum);
		}
	}
	
	const void pushdown(int p) {
		if (t[p].rev) {
			t[t[p].son[0]].reverse();
			t[t[p].son[1]].reverse();
			t[p].rev = 0;
		}
	}
	
	const int spawn(int w, bool f, bool g) {
		int p = top ? recycle[--top] : ++tail;
		t[p] = tree(w, f, g);
		return p;
	}
	
	const void reuse(int p) {
		recycle[top++] = p;
	}
	
	const void rotate(int p) {
		const bool f = identity(p);
		int fa = t[p].fa;
		int gfa = t[fa].fa;
		int q = t[p].son[f ^ 1];
		if (!isroot(fa)) {
			t[gfa].son[identity(fa)] = p;
		}
		t[t[p].son[f ^ 1] = fa].son[f] = q;
		t[t[t[q].fa = fa].fa = p].fa = gfa;
		pushup_Round(fa);
	}
	
	const void relieve(int p) {
		if (!isrothy(p)) {
			relieve(t[p].fa);
		}
		pushdown(p);
	}
	
	const void splay(int p) {
		relieve(p);
		for (int fa; !isrothy(p); rotate(p)) {
			if (!isrothy(fa = t[p].fa)) {
				rotate(identity(p) ^ identity(fa) ? p : fa);
			}
		}
		pushup_Round(p);
	}
	
	const void retwist(int p) {
		splay(t[t[p].fa].fa);
		if (!isrothy(t[t[p].fa].fa)) {
			splay(t[t[p].fa].fa);
			if (t[t[t[t[p].fa].fa].fa].son[0] == t[t[p].fa].fa) {
				rotate(t[t[p].fa].fa);
			}
		}
		bool f = identity(p);
		int fa = t[p].fa;
		int gfa = t[fa].fa;
		int ggfa = t[gfa].fa;
		if (!isroot(gfa)) {
			t[ggfa].son[1] = p;
		}
		t[p].fa = ggfa;
		connect(t[p].son[f ^ 1], gfa, f);
		connect(t[fa].son[f ^ 1], gfa, f ^ 1);
		connect(t[p].son[f], fa, f);
		connect(gfa, fa, f ^ 1);
		connect(fa, p, 0);
		t[p].son[1] = 0;
		pushup_Round(gfa);
		pushup_Square(fa);
		pushup_Round(p);
	}
	
	const void access(int x) {
		for (int y = 0; x; x = t[y = x].fa) {
			splay(x);
			if (t[t[x].fa].sqr) {
				retwist(x);
				splay(x);
			}
			t[x].son[1] = y;
			pushup_Round(x);
		}
	}
	
	const void makeroot(int x) {
		access(x);
		splay(x);
		t[x].reverse();
	}
	
	const void split(int x, int y) {
		makeroot(x);
		access(y);
		splay(y);
	}
	
	const void init() {
		for (int i = 0; i < n; i++) {
			spawn(0, 0, 0);
		}
	}
	
	const bool link(int x, int y, int z) {
		if (x == y) {
			return 0;
		}
		split(x, y);
		if (!t[x].fa) {
			int p = spawn(z, 0, 1);
			connect(p, x, 0);
			t[x].fa = y;
			pushup_Round(x);
			return 1;
		}
		t[y].son[0] = 0;
		splay(x);
		t[y].son[0] = x;
		if (t[x].ring) {
			return 0;
		}
		int p = spawn(z, 0, 1);
		int q = spawn(0, 1, 0);
		connect(t[x].son[1], q, 0);
		connect(p, q, 1);
		connect(q, x, 1);
		pushup_Square(q);
		pushup_Round(x);
		pushup_Round(y);
		return 1;
	}
	
	const bool cut(int x, int y, int z) {
		if (x == y) {
			return 0;
		}
		split(x, y);
		if (!t[x].fa) {
			return 0;
		}
		t[y].son[0] = 0;
		splay(x);
		t[y].son[0] = x;
		int &p = t[x].son[1];
		if (!t[p].sqr) {
			if (!t[p].edge || t[p].val ^ z) {
				return 0;
			}
			reuse(p);
			t[y].son[0] = t[x].fa = p = 0;
			pushup_Round(x);
			pushup_Round(y);
			return 1;
		}
		const bool f = t[p].son[1] && t[t[p].son[1]].val == z;
		if (!t[p].son[f] || t[t[p].son[f]].val ^ z) {
			return 0;
		}
		if (!f) {
			t[t[p].son[1]].reverse();
		}
		if (t[p].son[f ^ 1]) {
			t[t[p].son[f ^ 1]].fa = x;
		}
		reuse(p);
		reuse(t[p].son[f]);
		p = t[p].son[f ^ 1];
		pushup_Round(x);
		pushup_Round(y);
		return 1;
	}
	
	const int query(int x, int y) {
		if (x == y) {
			return 0;
		}
		split(x, y);
		return t[x].fa ? t[y].sum : -1;
	}
};

/*
定义: Link_Cut_Cactus t(n, m);

连边: t.link(u, v, w); 
若连边后仍为沙漠, 返回 true; 否则撤销操作, 返回 false.

断边: t.cut(u, v, w);
若存在这样的边, 返回 true; 否则返回 false.

最短路: t.query(u, v);
若不连通返回 -1.
*/
