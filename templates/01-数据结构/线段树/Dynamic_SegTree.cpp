/*
SegmentTree t(n);

t.add(x, v); 单点加 v，均摊 O(log n)。
t.query(l, r); 返回区间和，O(log n)。

t.build(a);
从完整数组重建，O(n)。
*/
struct Node {
	int sum = 0, l = 0, r = 0;
};
struct SegmentTree {
	int n, rt = 0;
	vector<Node> tr;
	SegmentTree(int n) : n(n), tr(1) {}
	int build(int l, int r, const vector<int> &a) {
		int p = tr.size();
		tr.push_back({});
		if (l == r) {
			tr[p].sum = a[l];
			return p;
		}
		int m = (l + r) / 2;
		int x = build(l, m, a), y = build(m + 1, r, a);
		tr[p] = {tr[x].sum + tr[y].sum, x, y};
		return p;
	}
	int add(int p, int l, int r, int pos, int val) {
		if (!p) {
			p = tr.size();
			tr.push_back({});
		}
		tr[p].sum += val;
		if (l < r) {
			int m = (l + r) / 2;
			if (pos <= m) {
				int q = add(tr[p].l, l, m, pos, val);
				tr[p].l = q;
			} else {
				int q = add(tr[p].r, m + 1, r, pos, val);
				tr[p].r = q;
			}
		}
		return p;
	}
	int query(int p, int l, int r, int ql, int qr) {
		if (!p || ql > r || qr < l) {
			return 0;
		}
		if (ql <= l && r <= qr) {
			return tr[p].sum;
		}
		int m = (l + r) / 2;
		return query(tr[p].l, l, m, ql, qr) + query(tr[p].r, m + 1, r, ql, qr);
	}
	void build(const vector<int> &a) {
		tr.assign(1, {});
		rt = build(1, n, a);
	}
	void add(int pos, int val) {
		rt = add(rt, 1, n, pos, val);
	}
	int query(int l, int r) {
		return query(rt, 1, n, l, r);
	}
};
