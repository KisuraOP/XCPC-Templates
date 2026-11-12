/*
左偏树，小根堆。

leftistTree G(n, m);
n 为集合个数，m 为插入次数上限。

以下操作的时间复杂度均为 O(log m)。

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
改为大根堆时，将 _merge() 中 vx > vy 的 > 改为 <。
*/
struct leftistTree {
	struct Node {
		int l, r, d, fa, v, tag;
		Node() : l(0), r(0), d(0), fa(0), v(0), tag(0) {}
	};
	vector<Node> a;
	vector<int> rt;
	vector<int> p, bel, sz;

	#define l(x) a[x].l
	#define r(x) a[x].r
	#define d(x) a[x].d
	#define fa(x) a[x].fa
	#define v(x) a[x].v
	#define tag(x) a[x].tag

	int _find(int x) {
		return p[x] == x ? x : p[x] = _find(p[x]);
	}
	void _union(int x, int y) {
		if (!rt[x]) {
			rt[x] = y;
			bel[_find(rt[x])] = x;
		} else {
			int z = _find(rt[x]);
			rt[x] = _merge(rt[x], y);
			fa(rt[x]) = 0;
			y = _find(y);
			if (z != y) {
				if (sz[z] < sz[y]) {
					swap(z, y);
				}
				p[y] = z;
				sz[z] += sz[y];
			}
			bel[z] = x;
		}
	}
	int _merge(int x, int y) {
		if (!x || !y) {
			return x | y;
		}
		int vx = v(x) + tag(x);
		int vy = v(y) + tag(y);
		if (vx > vy || (vx == vy && x > y)) {
			swap(x, y);
		}
		tag(y) -= tag(x);
		r(x) = _merge(r(x), y);
		fa(r(x)) = x;
		if (d(l(x)) < d(r(x))) {
			swap(l(x), r(x));
		}
		d(x) = d(r(x)) + 1;
		return x;
	}
	void _pushup(int x) {
		if (d(l(x)) < d(r(x))) {
			swap(l(x), r(x));
		}
		if (d(x) == d(r(x)) + 1) {
			return;
		}
		d(x) = d(r(x)) + 1;
		if (fa(x)) {
			_pushup(fa(x));
		}
	}

	leftistTree(int n, int m) : rt(n + 1), 
	p(max(n, m) + 1), bel(max(n, m) + 1), sz(m + 1, 1) {
		iota(p.begin(), p.end(), 0);
		a.reserve(m + 1);
		a.push_back(Node());
		d(0) = -1;
	}
	int insert(int x, int y) {
		a.push_back(Node());
		int z = a.size() - 1;
		v(z) = y;
		_union(x, z);
		return z;
	}
	int get(int x) {
		if (x >= a.size() || d(x) == -2) {
			return 0;
		}
		return bel[_find(x)];
	}
	void merge(int x, int y) {
		if (x == y || !rt[y]) {
			return;
		}
		_union(x, rt[y]);
		rt[y] = 0;
	}
	int top(int x) {
		return !rt[x] ? -inf : v(rt[x]) + tag(rt[x]);
	}
	void erase(int x) {
		if (x >= a.size() || d(x) == -2) {
			return;
		}
		if (l(x)) {
			tag(l(x)) += tag(x);
		}
		if (r(x)) {
			tag(r(x)) += tag(x);
		}
		int f = fa(x);
		int q = _merge(l(x), r(x));
		fa(q) = f;
		if (f == 0) {
			rt[get(x)] = q;
			if (q) {
				fa(q) = 0;
				bel[_find(q)] = get(x); 
			}
		} else {
			l(f) == x ? l(f) = q : r(f) = q;
			_pushup(f);
		}
		d(x) = -2; 
	}
	void modify(int x, int y) {
		if (x >= a.size() || d(x) == -2) {
			return;
		}
		int z = get(x);
		erase(x);
		d(x) = l(x) = r(x) = fa(x) = tag(x) = 0;
		v(x) = y; 
		_union(z, x);
	}
	void range_add(int x, int y) {
		if (rt[x]) {
			tag(rt[x]) += y;
		}
	}
};