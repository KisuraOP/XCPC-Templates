constexpr int N = 5e5 + 5;

struct Info {
	int sum, mn, mx;
	Info() : sum(0), mn(inf), mx(-inf) {}
	Info(int _s, int _mx, int _mn) : sum(_s), mx(_mx), mn(_mn) {}
} tr[N << 2];

int ta[N << 2], tc[N << 2];

Info operator+(const Info &a, const Info &b) {
	Info c;
	c.sum = a.sum + b.sum;
	c.mx = max(a.mx, b.mx);
	c.mn = min(a.mn, b.mn);
	return c;	
};

#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid (l + r >> 1)

void pushup(int p) {
	tr[p] = tr[ls] + tr[rs];
}
void build(int p, int l, int r, vector<int> &a) {
	if (l == r) {
		tr[p] = {a[l], a[l], a[l]};
		return ;
	}
	build(ls, l, mid, a);
	build(rs, mid + 1, r, a);
	pushup(p);
}
void apply(int p, int l, int r, int x, int y) {
	if (y != -1) {
		tr[p] = {(r - l + 1) * y, y, y};
		ta[p] = 0;
		tc[p] = y;
	}
	if (x > 0) {
		tr[p].sum += (r - l + 1) * x;
		tr[p].mn += x;
		tr[p].mx += x;
		ta[p] += x;
	}
}
void pushdown(int p, int l, int r) {
	apply(ls, l, mid, ta[p], tc[p]);
	apply(rs, mid + 1, r, ta[p], tc[p]);
	ta[p] = 0;
	tc[p] = -1;
}
void modify(int p, int l, int r, int ql, int qr, int x = 0, int y = -1) {
	if (ql <= l && qr >= r) {
		apply(p, l, r, x, y);
		return ;
	}
	pushdown(p, l, r);
	if (ql <= mid) {
		modify(ls, l, mid, ql, qr, x, y);
	}
	if (qr > mid) {
		modify(rs, mid + 1, r, ql, qr, x, y);
	}
	pushup(p);
}
Info query(int p, int l, int r, int ql, int qr) {
	if (ql <= l && qr >= r) {
		return tr[p];
	}
	pushdown(p, l, r);
	Info res;
	if (ql <= mid) {
		res = res + query(ls, l, mid, ql, qr);
	}
	if (qr > mid) {
		res = res + query(rs, mid + 1, r, ql, qr);
	}
	return res;
}