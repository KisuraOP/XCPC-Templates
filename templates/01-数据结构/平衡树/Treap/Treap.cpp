/*
Treap t(n); n 是容量，支持重复值。
t.insert(x); 插入一个 x。
t.erase(x); 删除一个 x，不存在时不操作。
t.size(); 元素个数。
t.select(x); < x 的元素个数，+1 为 x 的排名。
t.select(x, true); <= x 的元素个数。
t.count(x); x 的出现次数。
t.kth(k); 第 k 小的值，1-index。
t.getpre(x); 严格前驱，无解返回 -inf。
t.getnxt(x); 严格后继，无解返回 inf。
t.split(p, v, x, y); 按 < v 和 >= v 分裂树 p，根编号分别为 x、y。
t.split(p, v, x, y, true); 按 <= v 和 > v 分裂。
t.rt = t.merge(x, y); 合并 x、y，要求 x 中的值均 <= y 中的值。
t.rt 为根编号，t.a 为节点数组，0 为空节点。
以上操作期望 O(log n)。
*/
struct Treap {
	struct Node {
		int l = 0, r = 0, sz = 0, v = 0;
		unsigned long long pr = 0;
	};
	vector<Node> a;
	vector<int> bin;
	int rt = 0, tot = 0;
	mt19937_64 rng;
	Treap(int n) : a(n + 1), rng(chrono::steady_clock::now().time_since_epoch().count()) {
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
		a[p] = {0, 0, 1, v, rng()};
		return p;
	}
	void up(int p) {
		a[p].sz = a[a[p].l].sz + a[a[p].r].sz + 1;
	}
	void split(int p, int v, int &x, int &y, bool eq = false) {
		if (!p) {
			x = y = 0;
			return;
		}
		if (a[p].v < v || eq && a[p].v == v) {
			x = p;
			split(a[p].r, v, a[p].r, y, eq);
		} else {
			y = p;
			split(a[p].l, v, x, a[p].l, eq);
		}
		up(p);
	}
	int merge(int x, int y) {
		if (!x || !y) {
			return x | y;
		}
		if (a[x].pr < a[y].pr) {
			a[x].r = merge(a[x].r, y);
			up(x);
			return x;
		}
		a[y].l = merge(x, a[y].l);
		up(y);
		return y;
	}
	int size() {
		return a[rt].sz;
	}
	void insert(int v) {
		int x, y, p = make(v);
		split(rt, v, x, y);
		rt = merge(merge(x, p), y);
	}
	int pop(int p) {
		if (!a[p].l) {
			bin.push_back(p);
			return a[p].r;
		}
		a[p].l = pop(a[p].l);
		up(p);
		return p;
	}
	void erase(int v) {
		int x, y, z;
		split(rt, v, x, y);
		split(y, v, y, z, true);
		if (y) {
			y = pop(y);
		}
		rt = merge(merge(x, y), z);
	}
	int select(int v, bool eq = false) {
		int p = rt, res = 0;
		while (p) {
			if (a[p].v < v || eq && a[p].v == v) {
				res += a[a[p].l].sz + 1;
				p = a[p].r;
			} else {
				p = a[p].l;
			}
		}
		return res;
	}
	int count(int v) {
		return select(v, true) - select(v);
	}
	int kth(int k) {
		int p = rt;
		while (k != a[a[p].l].sz + 1) {
			if (k <= a[a[p].l].sz) {
				p = a[p].l;
			} else {
				k -= a[a[p].l].sz + 1;
				p = a[p].r;
			}
		}
		return a[p].v;
	}
	int getpre(int v) {
		int k = select(v);
		return k ? kth(k) : -inf;
	}
	int getnxt(int v) {
		int k = select(v, true);
		return k < size() ? kth(k + 1) : inf;
	}
};
