template<class Info>
struct SegmentTree {
	int n;
	vector<Info> tr;
	SegmentTree(vector<int> &a) {
		vector<Info> b(a.size());
		for (int i = 0; i < a.size(); i++) {
			b[i] = a[i];
		}
		init(b);
	}
	SegmentTree(vector<Info> &a) {
		init(a);
	}
	void init(vector<Info> &a) {
		n = a.size() - 1;
		tr.assign((4 << __lg(n + 1)) + 5, Info());
		build(1, 1, n, a);
	}
	#define ls (p << 1)
	#define rs (p << 1 | 1)
	void build(int p, int l, int r, vector<Info> &a) {
		if (l == r) {
			tr[p] = a[l];
			return ;
		}
		int m = l + r >> 1;
		build(ls, l, m, a);
		build(rs, m + 1, r, a);
		pushup(p);
	}
	void pushup(int p) {
		tr[p] = tr[ls] + tr[rs];
	}
	void modify(int p, int l, int r, int pos, const Info &x) {
		if (l == r) {
			tr[p] = x;
			return;
		}
		int m = l + r >> 1;
		if (pos <= m) {
			modify(ls, l, m, pos, x);
		} else {
			modify(rs, m + 1, r, pos, x);
		}
		pushup(p);
	}
	void modify(int pos, const Info &x) {
		modify(1, 1, n, pos, x);
	}
	Info query(int p, int l, int r, int ql, int qr) {
		if (l > qr || r < ql) {
			return Info();
		}
		if (ql <= l && qr >= r) {
			return tr[p];
		}
		int m = l + r >> 1;
		return query(ls, l, m, ql, qr) + query(rs, m + 1, r, ql, qr);
	}
	Info query(int ql, int qr) {
		if (ql > qr) {
			return Info();
		}
		return query(1, 1, n, ql, qr);
	}
	template<class F>
	int findFirst(int p, int l, int r, int ql, int qr, F &&pred) {
		if (l > qr || r < ql) {
			return -1;
		}
		if (ql <= l && qr >= r && !pred(tr[p])) {
			return -1;
		}
		if (l == r) {
			return l;
		}
		int m = l + r >> 1;
		int res = findFirst(ls, l, m, ql, qr, pred);
		if (res == -1) {
			res = findFirst(rs, m + 1, r, ql, qr, pred);
		}
		return res;
	}
	template<class F>
	int findFirst(int ql, int qr, F &&pred) {
		if (ql > qr) {
			return -1;
		}
		return findFirst(1, 1, n, ql, qr, pred);
	}
	template<class F>
	int findLast(int p, int l, int r, int ql, int qr, F &&pred) {
		if (l > qr || r < ql) {
			return -1;
		}
		if (ql <= l && qr >= r && !pred(tr[p])) {
			return -1;
		}
		if (l == r) {
			return l;
		}
		int m = l + r >> 1;
		int res = findLast(rs, m + 1, r, ql, qr, pred);
		if (res == -1) {
			res = findLast(ls, l, m, ql, qr, pred);
		}
		return res;
	}
	template<class F>
	int findLast(int ql, int qr, F &&pred) {
		if (ql > qr) {
			return -1;
		}
		return findLast(1, 1, n, ql, qr, pred);
	}
	#undef ls
	#undef rs
};

struct Info {
	Info() {}
	Info() {
	}
};
Info operator+(const Info &a, const Info &b) {
	Info c;
	return c;
};