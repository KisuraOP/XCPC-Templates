// 依赖 Stirling_Number_Base.cpp、Stirling_Number_Shift.cpp。
// 同一行无符号第一类斯特林数 O(N log N)
// {s(n, 0), s(n, 1), ..., s(n, n)}
vector<int> stirl1_row(int n) {
	if (n == 0) {
		return {1};
	}
	int h = 0;
	while ((1LL << h) <= n) {
		h++;
	}
	vector<int> res = {0, 1};
	int cur = 1; 
	for (int i = h - 2; i >= 0; i--) {
		auto shifted = poly_shift(res, cur);
		res = res * shifted;
		res.resize(cur * 2 + 1);
		cur *= 2;
		if ((n >> i) & 1) {
			vector<int> nres(cur + 2, 0);
			for (int j = 0; j <= cur; j++) {
				nres[j + 1] = (nres[j + 1] + res[j]) % mod;
				nres[j] = (nres[j] + res[j] * cur) % mod;
			}
			res = move(nres);
			cur++;
		}
	}
	return res;
}

