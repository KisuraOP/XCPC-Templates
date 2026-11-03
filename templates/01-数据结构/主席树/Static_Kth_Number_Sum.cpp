// 依赖 Static_Kth_Number.cpp。
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
		// 区间前 k 小的数的和
		cout << kth_sum(rt[l - 1], rt[r], k) << "\n";
	}
}
