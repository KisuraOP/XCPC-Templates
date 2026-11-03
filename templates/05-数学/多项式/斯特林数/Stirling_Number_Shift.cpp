// 依赖 Stirling_Number_Base.cpp。
vector<int> poly_shift(const vector<int> &A, int c) {
	int d = A.size() - 1;
	if (d < 0) {
		return {};
	}
	init(d);
	vector<int> f(d + 1), g(d + 1);
	for (int i = 0; i <= d; i++) {
		f[d - i] = A[i] * fac[i] % mod;
		g[i] = qpow(c, i) * invfac[i] % mod;
	}
	auto h = f * g;
	vector<int> B(d + 1);
	for (int j = 0; j <= d; j++) {
		B[j] = h[d - j] * invfac[j] % mod;
	}
	return B;
}

