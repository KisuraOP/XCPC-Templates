/*
依赖 Treap_Seq.cpp。

TreapVal t(n);
维护有序多重集合，支持重复值。

t.insert(x);
插入一个 x。

t.inc(x, v);
所有 >= x 的元素加 v，要求 v >= 0。

t.kth(k);
求第 k 小。

t.sum(l, r);
求值在 [l, r] 内的元素之和。

以上操作的时间复杂度均为期望 O(log n)。

示例：
TreapVal t(6);
t.insert(1);
t.insert(3);
t.insert(3);
t.insert(7);
t.inc(3, 2); // 1, 5, 5, 9
cout << t.kth(2); // 5
cout << t.sum(5, 9); // 19
*/
struct TreapVal : TreapSeq {
	TreapVal(int n) : TreapSeq(n) {}
	int select(int v, bool eq = false) {
		int p = rt, res = 0;
		while (p) {
			down(p);
			if (a[p].v < v || eq && a[p].v == v) {
				res += a[a[p].l].sz + 1;
				p = a[p].r;
			} else {
				p = a[p].l;
			}
		}
		return res;
	}
	void insert(int v) {
		TreapSeq::insert(select(v), v);
	}
	void inc(int v, int d) {
		int p = select(v), x, y;
		split(rt, p, x, y);
		apply(y, d);
		rt = merge(x, y);
	}
	int sum(int l, int r) {
		int x = select(l), y = select(r, true);
		return x < y ? ask(x + 1, y) : 0;
	}
};
