/*
LiChao G(L, R);
其中 L, R 是自变量 x 的取值范围。

G.insert({k, b});
插入直线 y = kx + b。

int res = G.query(x);
查询 max(kx + b)。

若要查询 min(kx + b), 进行如下修改
- Line 里 b(-inf) 改成 b(inf)
- insert 里 
  lo.F(mid) < hi.F(mid), 
  lo.F(l) < hi.F(l), 
  lo.F(r) < hi.F(r),
  三处小于号改成大于号
- query 里两个 max 改成 min, return -inf 改成 inf

int 可以换成 double。
*/

struct Line {
	int k, b;
	Line() : k(0), b(-inf) {}
	Line(int _k, int _b) : k(_k), b(_b) {} 
	int F(int x) {
		return k * x + b;
	}
};

struct LiChao {
	struct Node {
		Line x;
		int l, r;
		Node() : x(Line()), l(0), r(0) {}
	};
	int L, R;
	vector<Node> seg;
	LiChao(int l, int r) : L(l), R(r) {
		// 如果 runtime error, 尝试取消下面一行的注释
		// seg.reserve(2e7);
		seg.push_back({});
		seg.push_back({});
	}
	int get(int &p) {
		if (p == 0) {
			p = seg.size();
			seg.push_back({});
		}
		return p;
	}
	void insert(int p, int l, int r, Line x) {
		int mid = l + r >> 1;
		Line lo = seg[p].x, hi = x;
		if (lo.F(mid) < hi.F(mid)) {
			swap(lo, hi);
		}
		seg[p].x = lo;
		if (lo.F(l) < hi.F(l)) {
			insert(get(seg[p].l), l, mid, hi);
		} else if (lo.F(r) < hi.F(r)) {
			insert(get(seg[p].r), mid + 1, r, hi);
		}
	}
	void insert(Line x) {
		insert(1, L, R, x);
	}
	int query(int p, int l, int r, int x) {
		if (p == 0) {
			return -inf;
		}
		int mid = l + r >> 1;
		int res = seg[p].x.F(x);
		if (l == r) {
			return res;
		}
		if (x <= mid) {
			return max(res, query(seg[p].l, l, mid, x));
		} else {
			return max(res, query(seg[p].r, mid + 1, r, x));
		}
	}
	int query(int x) {
		return query(1, L, R, x);
	}
};