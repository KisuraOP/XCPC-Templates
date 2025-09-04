struct Line {
    int k, b; // y = kx + b;
    Line() : k(0), b(-1e18) {}
    Line(int _k, int _b) : k(_k), b(_b) {} 
    int F(int x) {
        return k * x + b;
    }
};

struct LiChao {
    int L, R; // 自变量 x 的取值范围
    vector<Line> seg;
    LiChao(int l, int r) : L(l), R(r) {
        seg.assign(4 * (R - L + 1) + 5, Line());
    }
    void insert(int p, int l, int r, Line x) {
        int mid = l + r >> 1;
        Line lo = seg[p], hi = x;
        if (lo.F(mid) < hi.F(mid)) {
            swap(lo, hi);
        }
        seg[p] = lo;
        if (lo.F(l) < hi.F(l)) {
            insert(p << 1, l, mid, hi);
        } else if (lo.F(r) < hi.F(r)) {
            insert(p << 1 | 1, mid + 1, r, hi);
        }
    }
    void insert(Line x) {
        insert(1, L, R, x);
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