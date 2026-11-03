// 依赖 Stirling_Number_Base.cpp。
// 同一列无符号第一类斯特林数 O(N log N)
// {s(0, k), s(1, k), ..., s(n, k)}
vector<int> stirl1_col(int n, int k) {
	if (k > n) {
		return vector<int>(n + 1, 0);
	}
	if (k == 0) {
		vector<int> res(n + 1, 0);
		res[0] = 1;
		return res;
	}
	init(n);
	vector<int> A(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		A[i] = inv[i];
	}
	auto B = poly_pow(A, k, n + 1);
	int inv_k = invfac[k];
	for (int i = 0; i <= n; i++) {
		B[i] = B[i] * fac[i] % mod * inv_k % mod;
	}
	return B;
}
