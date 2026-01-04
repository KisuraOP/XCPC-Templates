/*
随机可并堆, all 1-index。

Random_Heap G(n, m);
其中 n 表示集合数量, m 表示往集合里插入的元素数量总和 (即插入操作的次数上限)。
集合编号为 1 ~ n。

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
若想改为大根堆, _merge() 中 v(x) > v(y) 改为 v(x) < v(y) 即可。
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
		return !p[x] ? 0 : bel[_get(x)];
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