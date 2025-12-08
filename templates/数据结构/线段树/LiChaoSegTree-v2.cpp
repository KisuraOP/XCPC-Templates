/*
insert(xl, xr, {k, b});
插入定义域 [xl, xr] 的线段 y = kx + b。
比无定义域版本多一个 log。

TODO：动态开点。
*/

struct Line {
    int k, b;
    Line() : k(0), b(-1e18) {}
    Line(int _k, int _b) : k(_k), b(_b) {} 
    int F(int x) {
        return k * x + b;
    }
};

struct LiChao {
    int L, R;
    vector<Line> seg;
    LiChao(int l, int r) : L(l), R(r) {
        seg.assign(4 * (R - L + 1) + 5, Line());
    }
    void update(int p, int l, int r, Line x) {
        int mid = l + r >> 1;
        Line lo = seg[p], hi = x;
        if (lo.F(mid) < hi.F(mid)) {
            swap(lo, hi);
        }
        seg[p] = lo;
        if (lo.F(l) < hi.F(l)) {
            update(p << 1, l, mid, hi);
        } else if (lo.F(r) < hi.F(r)) {
            update(p << 1 | 1, mid + 1, r, hi);
        }
    }
	void insert(int p, int l, int r, int xl, int xr, Line x) {
		if (xl <= l && xr >= r) {
			update(p, l, r, x);
			return ;
		}
		int mid = l + r >> 1;
		if (xl <= mid) {
			insert(p << 1, l, mid, xl, xr, x);
		}
		if (xr > mid) {
			insert(p << 1 | 1, mid + 1, r, xl, xr, x);
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
        int mid = l + r >> 1;
        int res = seg[p].F(x);
        if (l == r) {
            return res;
        }
        if (x <= mid) {
            return max(res, query(p << 1, l, mid, x));
        } else {
            return max(res, query(p << 1 | 1, mid + 1, r, x));
        }
    }
    int query(int x) {
        return query(1, L, R, x);
    }
};