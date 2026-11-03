// 依赖 Stirling_Number_Base.cpp。
// 同一行第二类斯特林数 O(N log N)
// {S(n, 0), S(n, 1), ..., S(n, n)}
vector<int> stirl2_row(int n) {
	if (n == 0) {
		return {1};
	}
	init(n);
	vector<int> a(n + 1), b(n + 1);
	for (int i = 0; i <= n; i++) {
		a[i] = (i % 2 == 1 ? mod - invfac[i] : invfac[i]);
		b[i] = qpow(i, n) * invfac[i] % mod;
	}
	auto res = a * b;
	res.resize(n + 1);
	return res;
}

