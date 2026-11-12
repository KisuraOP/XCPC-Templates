/*
随机可并堆，小根堆。

Random_Heap G(n, m);
n 为集合个数，m 为插入次数上限。

int id = insert(x, y);
向集合 x 插入值 y，返回元素编号。
元素编号从 1 开始依次递增。

int id = get(x);
返回元素 x 所在的集合编号；若元素不存在或已被删除，则返回 0。

int val = top(x);
返回集合 x 中的最小值；若集合为空，则返回 -inf。

erase(x);
删除元素 x。

modify(x, y);
将元素 x 的值改为 y。

merge(x, y);
将集合 y 中的元素并入集合 x，并清空集合 y。

range_add(x, y);
将集合 x 中每个元素的值加 y。

rt[x] 为集合 x 的堆顶元素编号。
改为大根堆时，将 _merge() 中 v(x) > v(y) 的 > 改为 <。
*/
struct Random_Heap {
	struct Node {
		int l, r, fa, v, tag;
		Node() : l(0), r(0), fa(0), v(0), tag(0) {}
	};
	vector<Node> a;
	vector<int> rt, p, bel;
	mt19937_64 rng;

	#define l(x) a[x].l
	#define r(x) a[x].r
	#define fa(x) a[x].fa
	#define v(x) a[x].v
	#define tag(x) a[x].tag

	void _pushdown(int x) {
		if (!x || !tag(x)) {
			return ;
		}
		if (l(x)) {
			v(l(x)) += tag(x);
			tag(l(x)) += tag(x);
		}
		if (r(x)) {
			v(r(x)) += tag(x);
			tag(r(x)) += tag(x);
		}
		tag(x) = 0;
	}
	int _merge(int x, int y) {
		if (!x || !y) {
			return x | y;
		}
		if (v(x) > v(y) || (v(x) == v(y) && x > y)) {
			swap(x, y);
		}
		_pushdown(x);
		r(x) = _merge(r(x), y);
		fa(r(x)) = x;
		if (rng() & 1) {
			swap(l(x), r(x));
		}
		return x;
	}
	void _union(int x, int y) {
		rt[x] = _merge(rt[x], y);
		if (rt[x]) {
			fa(rt[x]) = 0;
			bel[rt[x]] = x;
		}
	}
	int _get(int x) {
		vector<int> st;
		while (x) {
			st.push_back(x);
			x = fa(x);
		}
		reverse(st.begin(), st.end());
		for (auto x : st) {
			_pushdown(x);
		}
		return st[0];
	}

	Random_Heap(int n, int m) : rt(n + 1), 
	p(max(n, m) + 1), bel(max(n, m) + 1), rng(415411) {
		a.push_back(Node());
	}
	int insert(int x, int y) {
		a.push_back(Node());
		int z = a.size() - 1;
		v(z) = y;
		p[z] = 1;
		_union(x, z);
		return z;
	}
	int get(int x) {
		return x >= a.size() || !p[x] ? 0 : bel[_get(x)];
	}
	int top(int x) {
		return !rt[x] ? -inf : v(rt[x]);
	}
	void erase(int x) {
		if (!p[x]) {
			return ;
		}
		int z = _get(x), f = fa(x);
		int q = _merge(l(x), r(x));
		if (x == z) {
			rt[bel[z]] = q;
			if (q) {
				fa(q) = 0;
				bel[q] = bel[z];
			}
		} else {
			l(f) == x ? l(f) = q : r(f) = q;
			if (q) {
				fa(q) = f;
			}
		}
		p[x] = 0;
	}
	void modify(int x, int y) {
		if (!p[x]) {
			return ;
		}
		int z = get(x);
		erase(x);
		l(x) = r(x) = fa(x) = tag(x) = 0;
		v(x) = y;
		p[x] = 1;
		_union(z, x);
	}
	void merge(int x, int y) {
		if (x == y || !rt[y]) {
			return ;
		}
		_union(x, rt[y]);
		rt[y] = 0;
	}
	void range_add(int x, int y) {
		if (rt[x]) {
			v(rt[x]) += y;
			tag(rt[x]) += y;
		}
	}
};