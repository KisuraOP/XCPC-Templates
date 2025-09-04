struct Node {
    int sum;
    Node *l, *r;
    Node() : sum(0), l(nullptr), r(nullptr) {}
};
struct SegmentTree {
    Node* rt;
    int n;
    #define mid (l + r >> 1)
    Node* build(int l, int r, const vector<int> &a) {
        if (l == r) {
            Node* p = new Node();
            p->sum = a[l];
            return p;
        }
        Node* p = new Node();
        p->l = build(l, mid, a);
        p->r = build(mid + 1, r, a);
        p->sum = p->l->sum + p->r->sum;
        return p;
    }
    Node* update_add(Node* p, int l, int r, int pos, int val) {
        if (!p) {
            p = new Node();
        }
        if (l == r) {
            p->sum += val;
            return p;
        }
        if (pos <= mid) {
            p->l = update_add(p->l, l, mid, pos, val);
        } else {
            p->r = update_add(p->r, mid + 1, r, pos, val);
        }
        p->sum = (p->l ? p->l->sum : 0) + (p->r ? p->r->sum : 0);
        return p;
    }
    int range_query(Node* p, int l, int r, int ql, int qr) {
        if (!p || ql > r || qr < l) {
            return 0;
        }
        if (ql <= l && qr >= r) {
            return p->sum;
        }
        int lsum = range_query(p->l, l, mid, ql, qr);
        int rsum = range_query(p->r, mid + 1, r, ql, qr);
        return lsum + rsum;
    }

    SegmentTree(int n) {
        rt = nullptr;
        this->n = n;
    }
    void build(const vector<int>& nums) {
        rt = build(1, n, nums);
    }
    void add(int pos, int val) {
        rt = update_add(rt, 1, n, pos, val);
    }
    int query(int l, int r) {
        return range_query(rt, 1, n, l, r);
    }
};