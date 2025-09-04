template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    vector<Info> tr;
    vector<Tag> tag;
    LazySegmentTree(vector<Info> &a) {
        n = a.size() - 1;
        const int N = (4 << __lg(n + 1)) + 5;
        tr.assign(N, Info());
        tag.assign(N, Tag());
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
    void apply(int p, const Tag &x) {
        tr[p].apply(x);
        tag[p].apply(x);
    }
    void pushdown(int p) {
        apply(ls, tag[p]);
        apply(rs, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int pos, const Info &x) {
        if (l == r) {
            tr[p] = x;
            return;
        }
        pushdown(p);
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
        if (ql <= l && qr >= r) {
            return tr[p];
        }
        int m = l + r >> 1;
        pushdown(p);
        if (qr <= m) {
            return query(ls, l, m, ql, qr);
        } else if (ql >= m + 1) {
            return query(rs, m + 1, r, ql, qr);
        } else {
            return query(ls, l, m, ql, qr) + query(rs, m + 1, r, ql, qr);
        }
    }
    Info query(int ql, int qr) {
        return query(1, 1, n, ql, qr);
    }
    void modify(int p, int l, int r, int ql, int qr, const Tag &x) {
        if (l > qr || r < ql) {
            return ;
        }
        if (ql <= l && qr >= r) {
            apply(p, x);
            return ;
        }
        pushdown(p);
        int m = l + r >> 1;
        modify(ls, l, m, ql, qr, x);
        modify(rs, m + 1, r, ql, qr, x);
        pushup(p);
    }
    void modify(int ql, int qr, const Tag &x) {
        return modify(1, 1, n, ql, qr, x);
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
        pushdown(p);
        int m = l + r >> 1;
        int res = findFirst(ls, l, m, ql, qr, pred);
        if (res == -1) {
            res = findFirst(rs, m + 1, r, ql, qr, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int ql, int qr, F &&pred) {
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
        pushdown(p);
        int m = l + r >> 1;
        int res = findLast(rs, m + 1, r, ql, qr, pred);
        if (res == -1) {
            res = findLast(ls, l, m, ql, qr, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int ql, int qr, F &&pred) {
        return findLast(1, 1, n, ql, qr, pred);
    }
};
 
struct Tag {
    Z mul = 1;
    Z add = 0;

    Tag() {}
    Tag(int A, int B) {
        mul = A;
        add = B;
    }
    void apply(const Tag &t) & {
        add *= t.mul;
        mul *= t.mul;
        add += t.add;
    }
};
 
struct Info {
    Z sum = 0;
    int len = 1;
    
    Info() {}
    Info(Z A) {
        sum = A;
    }
    void apply(const Tag &t) & {
        sum *= t.mul;
        sum += t.add * len;
    }
};
 
Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.len = a.len + b.len;
    return c;
}