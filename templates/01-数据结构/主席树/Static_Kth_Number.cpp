constexpr int N = 1e6 + 5;

struct Info {
	int sum = 0;
	int vs = 0;
	int l = 0, r = 0;
} tr[N << 5];

int tot = 0;

#define ls(x) (tr[x].l)
#define rs(x) (tr[x].r)
#define sum(x) (tr[x].sum)
#define vs(x) (tr[x].vs)

void pushup(int p) {
	sum(p) = sum(ls(p)) + sum(rs(p));
	vs(p) = vs(ls(p)) + vs(rs(p));
}
void update(int lst, int now, int pos, int k, int l = -1e9, int r = 1e9) {
	if (l == r) {
		sum(now) = sum(lst) + k;
		vs(now) = vs(lst) + k * pos;
		return ;
	}
	ls(now) = ls(lst);
	rs(now) = rs(lst);
 	int mid = l + r >> 1;
	if (pos <= mid) {
		ls(now) = ++tot;
		update(ls(lst), ls(now), pos, k, l, mid);
	} else {
		rs(now) = ++tot;
		update(rs(lst), rs(now), pos, k, mid + 1, r);
	}
	pushup(now);
}
int kth(int lst, int now, int k, int l = -1e9, int r = 1e9) {
	if (l == r) {
		return l;
	}
	int mid = l + r >> 1;
	int val = sum(ls(now)) - sum(ls(lst));
	if (val >= k) {
		return kth(ls(lst), ls(now), k, l, mid);
	} else {
		return kth(rs(lst), rs(now), k - val, mid + 1, r);
	}
}
int kth_sum(int lst, int now, int k, int l = -1e9, int r = 1e9) {
	if (l == r) {
		return l * k;
	}
	int mid = l + r >> 1;
	int val = sum(ls(now)) - sum(ls(lst));
	if (val >= k) {
		return kth_sum(ls(lst), ls(now), k, l, mid);
	} else {
		return vs(ls(now)) - vs(ls(lst)) + kth_sum(rs(lst), rs(now), k - val, mid + 1, r);
	}
}

void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	vector<int> rt(n + 1);
	for (int i = 1; i <= n; i++) {
		rt[i] = ++tot;
		update(rt[i - 1], rt[i], a[i], 1);
	}
	while (m--) {
		int l, r, k;
		cin >> l >> r >> k;
		// 区间第 k 小的数
		cout << kth(rt[l - 1], rt[r], k) << "\n";
		// 区间前 k 小的数的和
		cout << kth_sum(rt[l - 1], rt[r], k) << "\n";
	}
}