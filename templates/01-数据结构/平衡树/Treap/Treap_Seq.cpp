/*
TreapSeq t(n); n 是容量。
t.size(); 序列长度。
t.insert(k, x); 在第 k 个元素后插入 x，k = 0 时插入开头。
t.add(l, r, x); [l, r] 每个数加 x。
t.flip(l, r); 翻转 [l, r]。
t.ask(l, r); [l, r] 的和。
t.kth(k); 第 k 个元素的值。
t.split(p, k, x, y); 按前 k 个和剩余元素分裂树 p，根编号分别为 x、y。
t.rt = t.merge(x, y); 将 y 接在 x 后面，返回根编号。
以上操作期望 O(log n)。

t.build(v); 用 v 重建序列。
t.erase(l, r); 删除 [l, r]，期望 O(log n + r-l)。
t.range(l, r, f); 用 f(p) 查询或修改 [l, r]，p 为区间子树的根编号。
f 的参数为 int &p 时，可以更换子树根。

翻转 [l, r]：
t.range(l, r, [&](int p) {
    t.flip(p);
});

求和后删除 [l, r]：
int res;
t.range(l, r, [&](int &p) {
    res = t.a[p].sum;
    t.drop(p);
    p = 0;
});
t.rt 为根编号，t.a 为节点数组，0 为空节点。
*/
struct TreapSeq {
	struct Node {
		int l = 0, r = 0, sz = 0, v = 0, sum = 0, tag = 0, rev = 0;
		unsigned long long pr = 0;
	};
	vector<Node> a;
	vector<int> bin;
	int rt = 0, tot = 0;
	mt19937_64 rng;
	TreapSeq(int n) : a(n + 1), rng(chrono::steady_clock::now().time_since_epoch().count()) {
		bin.reserve(n);
	}
	int make(int v) {
		int p;
		if (bin.empty()) {
			p = ++tot;
		} else {
			p = bin.back();
			bin.pop_back();
		}
		a[p] = {0, 0, 1, v, v, 0, 0, rng()};
		return p;
	}
	void drop(int p) {
		if (p) {
			drop(a[p].l);
			drop(a[p].r);
			bin.push_back(p);
		}
	}
	void up(int p) {
		a[p].sz = a[a[p].l].sz + a[a[p].r].sz + 1;
		a[p].sum = a[a[p].l].sum + a[a[p].r].sum + a[p].v;
	}
	void apply(int p, int v) {
		if (p) {
			a[p].v += v;
			a[p].sum += v * a[p].sz;
			a[p].tag += v;
		}
	}
	void flip(int p) {
		if (p) {
			swap(a[p].l, a[p].r);
			a[p].rev ^= 1;
		}
	}
	void down(int p) {
		if (a[p].tag) {
			apply(a[p].l, a[p].tag);
			apply(a[p].r, a[p].tag);
			a[p].tag = 0;
		}
		if (a[p].rev) {
			flip(a[p].l);
			flip(a[p].r);
			a[p].rev = 0;
		}
	}
	void split(int p, int k, int &x, int &y) {
		if (!p) {
			x = y = 0;
			return;
		}
		down(p);
		if (a[a[p].l].sz < k) {
			x = p;
			split(a[p].r, k - a[a[p].l].sz - 1, a[p].r, y);
		} else {
			y = p;
			split(a[p].l, k, x, a[p].l);
		}
		up(p);
	}
	int merge(int x, int y) {
		if (!x || !y) {
			return x | y;
		}
		if (a[x].pr < a[y].pr) {
			down(x);
			a[x].r = merge(a[x].r, y);
			up(x);
			return x;
		}
		down(y);
		a[y].l = merge(x, a[y].l);
		up(y);
		return y;
	}
	void build(const vector<int> &v) {
		drop(rt);
		rt = 0;
		vector<int> st;
		for (int i = 1; i < v.size(); i++) {
			int p = make(v[i]), q = 0;
			while (!st.empty() && a[st.back()].pr > a[p].pr) {
				q = st.back();
				st.pop_back();
				up(q);
			}
			a[p].l = q;
			if (!st.empty()) {
				a[st.back()].r = p;
			}
			st.push_back(p);
		}
		while (!st.empty()) {
			rt = st.back();
			st.pop_back();
			up(rt);
		}
	}
	int size() {
		return a[rt].sz;
	}
	template<class F>
	void range(int l, int r, F f) {
		int x, y, z;
		split(rt, r, y, z);
		split(y, l - 1, x, y);
		f(y);
		rt = merge(merge(x, y), z);
	}
	void insert(int k, int v) {
		int x, y, p = make(v);
		split(rt, k, x, y);
		rt = merge(merge(x, p), y);
	}
	void erase(int l, int r) {
		range(l, r, [&](int &p) {
			drop(p);
			p = 0;
		});
	}
	void add(int l, int r, int v) {
		range(l, r, [&](int p) {
			apply(p, v);
		});
	}
	void flip(int l, int r) {
		range(l, r, [&](int p) {
			flip(p);
		});
	}
	int ask(int l, int r) {
		int res;
		range(l, r, [&](int p) {
			res = a[p].sum;
		});
		return res;
	}
	int kth(int k) {
		int p = rt;
		while (true) {
			down(p);
			int s = a[a[p].l].sz;
			if (k == s + 1) {
				return a[p].v;
			}
			if (k <= s) {
				p = a[p].l;
			} else {
				k -= s + 1;
				p = a[p].r;
			}
		}
	}
};
