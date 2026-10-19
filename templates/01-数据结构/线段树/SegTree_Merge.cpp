template<class Info, class Tag>
struct Merge_SegTree {
	int n, tot;
	vector<Info> tr;
	vector<Tag> tag;
	vector<int> lc, rc;
	vector<int> del;

	// M 是最大节点数, 通常是 nlogn 的常数倍
	Merge_SegTree(int n, int M) : n(n), tot(0), tr(M + 1), tag(M + 1), lc(M + 1), rc(M + 1) {}

	int new_node() {
		int p;
		if (!del.empty()) {
			p = del.back();
			del.pop_back();
		} else {
			p = ++tot;
		}
		tr[p] = Info();
		tag[p] = Tag();
		lc[p] = rc[p] = 0;
		return p;
	}
	void del_node(int p) {
		del.push_back(p);
	}
	void pushup(int p) {
		tr[p] = Info();
		if (lc[p]) {
			tr[p] = tr[p] + tr[lc[p]];
		}
		if (rc[p]) {
			tr[p] = tr[p] + tr[rc[p]];
		}
	}
	void apply(int p, const Tag &x) {
		if (p) {
			tr[p].apply(x);
			tag[p].apply(x);
		}
	}
	void pushdown(int p) {
		if (!tag[p].has_tag()) {
			return ;
		}
		apply(lc[p], tag[p]);
		apply(rc[p], tag[p]);
		tag[p] = Tag();
	}
	void modify(int &p, int l, int r, int pos, const Info &x) {
		if (!p) {
			p = new_node();
		}
		if (l == r) {
			tr[p].merge(x);
			return ;
		}
		pushdown(p);
		int mid = l + r >> 1;
		if (pos <= mid) {
			modify(lc[p], l, mid, pos, x);
		} else {
			modify(rc[p], mid + 1, r, pos, x);
		}
		pushup(p);
	}
	void modify(int &rt, int pos, const Info &x) {
		modify(rt, 1, n, pos, x);
	}
	void modify(int &p, int l, int r, int ql, int qr, const Tag &x) {
		if (!p || l > qr || r < ql) {
			return ;
		}
		if (ql <= l && qr >= r) {
			apply(p, x);
			return ;
		}
		pushdown(p);
		int mid = l + r >> 1;
		modify(lc[p], l, mid, ql, qr, x);
		modify(rc[p], mid + 1, r, ql, qr, x);
		pushup(p);
	}
	void modify(int &rt, int ql, int qr, const Tag &x) {
		modify(rt, 1, n, ql, qr, x);
	}
	Info query(int p, int l, int r, int ql, int qr) {
		if (!p || l > qr || r < ql) {
			return Info();
		}
		if (ql <= l && qr >= r) {
			return tr[p];
		}
		pushdown(p);
		int mid = l + r >> 1;
		if (qr <= mid) {
			return query(lc[p], l, mid, ql, qr);
		}
		if (ql > mid) {
			return query(rc[p], mid + 1, r, ql, qr);
		}
		return query(lc[p], l, mid, ql, qr) + query(rc[p], mid + 1, r, ql, qr);
	}
	Info query(int rt, int ql, int qr) {
		return query(rt, 1, n, ql, qr);
	}
	int merge(int p, int q, int l, int r) {
		if (!p || !q) {
			return p | q;
		}
		if (l == r) {
			tr[p].merge(tr[q]);
			del_node(q);
			return p;
		}
		pushdown(p);
		pushdown(q);
		int mid = l + r >> 1;
		lc[p] = merge(lc[p], lc[q], l, mid);
		rc[p] = merge(rc[p], rc[q], mid + 1, r);
		pushup(p);
		del_node(q);
		return p;
	}
	void merge(int &rt1, int rt2) {
		rt1 = merge(rt1, rt2, 1, n);
	}
};


// 单点修改, 单点极值(记录下标)
struct Tag {
	bool has_tag() const {
		return false;
	}
	void apply(const Tag &t) & {
	}
};
struct Info {
	int sum = 0, pos = 0;
	Info() {}
	Info(int x, int y) : sum(x), pos(y) {}
	void apply(const Tag &t) & {
	}
	void merge(const Info &oth) {
		sum += oth.sum;
		pos = oth.pos;
	}
};
Info operator+(const Info &a, const Info &b) {
	Info c;
	if (!a.pos) {
		return b;
	}
	if (!b.pos) {
		return a;
	}
	if (a.sum >= b.sum) {
		c.pos = a.pos;
		c.sum = a.sum;
	} else  {
		c.pos = b.pos;
		c.sum = b.sum;
	}
	return c;
}


// 区间加, 区间查
struct Tag {
	int add = 0;
	Tag() {}
	Tag(int A) : add(A) {}
	bool has_tag() const {
		return add != 0;
	}
	void apply(const Tag &t) & {
		add += t.add;
	}
};
struct Info {
	int sum = 0, len = 0;
	Info() {}
	Info(int x, int y = 1) : sum(x), len(y) {}
	void apply(const Tag &t) & {
		sum += t.add * len;
	}
	void merge(const Info &oth) {
		len = 1;
		sum += oth.sum;
	}
};
Info operator+(const Info &a, const Info &b) {
	Info c;
	c.sum = a.sum + b.sum;
	c.len = a.len + b.len;
	return c;
}


// 区间赋值, 区间查
struct Tag {
	int cov = 0;
	bool has_cov = false;
	Tag() {}
	Tag(int x) : cov(x), has_cov(true) {}
	bool has_tag() const {
		return has_cov;
	}
	void apply(const Tag &t) & {
		if (t.has_cov) {
			cov = t.cov;
			has_cov = true;
		}
	}
};
struct Info {
	int sum = 0, len = 0;
	Info() {}
	Info(int x, int y = 1) : sum(x), len(y) {}
	void apply(const Tag &t) & {
		if (t.has_cov) {
			sum = t.cov * len;
		}
	}
	void merge(const Info &oth) {
		len = 1;
		sum = oth.sum;
	}
};
Info operator+(const Info &a, const Info &b) {
	Info c;
	c.sum = a.sum + b.sum;
	c.len = a.len + b.len;
	return c;
}


// 区间乘 + 加
struct Tag {
	int mul = 1, add = 0;
	Tag() {}
	Tag(int x, int y) : mul(x), add(y) {}
	bool has_tag() const {
		return mul != 1 || add != 0;
	}
	void apply(const Tag &t) & {
		add *= t.mul;
		mul *= t.mul;
		add += t.add;
	}
};
struct Info {
	int sum = 0, len = 0;
	Info() {}
	Info(int x, int y = 1) : sum(x), len(y) {}
	void apply(const Tag &t) & {
		sum *= t.mul;
		sum += t.add * len;
	}
	void merge(const Info &oth) {
		len = 1;
		sum += oth.sum;
	}
};
Info operator+(const Info &a, const Info &b) {
	Info c;
	c.sum = a.sum + b.sum;
	c.len = a.len + b.len;
	return c;
}