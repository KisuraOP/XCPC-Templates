/*
insert(xl, xr, {k, b});
插入定义域 [xl, xr] 的线段 y = kx + b。
比无定义域版本多一个 log。
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
		seg.reserve(2e7);
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
    void update(int p, int l, int r, Line x) {
        int mid = l + r >> 1;
        Line lo = seg[p].x, hi = x;
        if (lo.F(mid) < hi.F(mid)) {
            swap(lo, hi);
        }
        seg[p].x = lo;
        if (lo.F(l) < hi.F(l)) {
            update(get(seg[p].l), l, mid, hi);
        } else if (lo.F(r) < hi.F(r)) {
            update(get(seg[p].r), mid + 1, r, hi);
        }
    }
	void insert(int p, int l, int r, int xl, int xr, Line x) {
		if (xl <= l && xr >= r) {
			update(p, l, r, x);
			return ;
		}
		int mid = l + r >> 1;
		if (xl <= mid) {
			insert(get(seg[p].l), l, mid, xl, xr, x);
		}
		if (xr > mid) {
			insert(get(seg[p].r), mid + 1, r, xl, xr, x);
		}
	}
    void insert(int xl, int xr, Line x) {
    	if (xl > xr) {
    		return ;
    	} 
    	assert(xl >= L && xr <= R);
        insert(1, L, R, xl, xr, x);
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