/*
左偏树(小根堆), all 1-index。

leftistTree G(n, m);
其中 n 表示集合数量, m 表示往集合里插入的元素数量总和 (即插入操作的次数上限)。
集合编号为 1 ~ n。

以下每一种操作的时间复杂度均不高于 O(log m)。

int id = insert(x, y);
往编号为 x 的集合里插入一个值为 y 的元素, 返回该元素的编号。
元素编号默认从 1 开始递增。

int id = get(x);
返回编号为 x 的元素所在的集合的编号。
若编号为 x 的元素不存在或已经被删去, 返回 0。

int val = top(x);
返回编号为 x 的集合中最小的元素的值。
如果编号为 x 的集合为空, 返回 -inf。

erase(x);
把编号为 x 的元素删去。

modify(x, y);
把编号为 x 的元素的值更改为 y。

merge(x, y);
把编号为 y 的集合中的所有元素并入编号为 x 的集合中, 并把编号为 y 的集合清空。

range_add(x, y);
把编号为 x 的集合里的所有元素的值加上 y。

rt[x] 表示编号为 x 的集合的堆顶元素的编号。
若想改为大根堆, _merge() 中 vx > vy 改为 vx < vy 即可。
*/
struct leftistTree {
	struct Node {
		int l, r, d, fa, v, tag;
		Node() : l(0), r(0), d(0), fa(0), v(0), tag(0) {}
	};
	vector<Node> a;
	vector<int> rt;
	vector<int> p, bel;

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
			int z = rt[x];
			rt[x] = _merge(rt[x], y);
			fa(rt[x]) = 0;
			p[_find(z)] = _find(rt[x]);
			p[_find(y)] = _find(rt[x]);
			bel[_find(rt[x])] = x;
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
	p(max(n, m) + 1), bel(max(n, m) + 1) {
		iota(p.begin(), p.end(), 0);
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