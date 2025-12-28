constexpr int N = 4e7 + 5;

struct Node {
	int l, r, cnt;
} t[N];

int tot = 0;
int build(int l, int r) {
	int p = ++tot;
	if (l == r) {
		return p;
	}
	int mid = l + r >> 1;
	t[p].l = build(l, mid);
	t[p].r = build(mid + 1, r);
	return p;
}
int insert(int p, int i, int l, int r, int x) {
	int q = ++tot;
	t[q] = t[p];
	t[q].cnt += x;
	if (l < r) {
		int mid = l + r >> 1;
		if (i <= mid) {
			t[q].l = insert(t[p].l, i, l, mid, x);
		} else {
			t[q].r = insert(t[p].r, i, mid + 1, r, x);
		}
	}
	return q;
}
int query(int i, int q, int l, int r) {
	if (l == r) {
		return t[q].cnt;
	}
	int mid = l + r >> 1;
	if (i <= mid) {
		return query(i, t[q].l, l, mid) + t[t[q].r].cnt;
	} else {
		return query(i, t[q].r, mid + 1, r);
	}
}
void solve() {
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	
	vector<int> rt(n + 1);
	rt[0] = build(1, n);
	vector<int> lst(1e6 + 1);
	for (int i = 1; i <= n; i++) {
		if (lst[a[i]] == 0) {
			rt[i] = insert(rt[i - 1], i, 1, n, 1);
		} else {
			int t = insert(rt[i - 1], lst[a[i]], 1, n, -1);
			rt[i] = insert(t, i, 1, n, 1);
		}
		lst[a[i]] = i;
	}

	auto ask = [&] (int l, int r) {
		return query(l, rt[r], 1, n);
	};

	int q;
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		cout << ask(l, r) << "\n";
	}
}