// 依赖 Poly_Mul.cpp、Poly_Base.cpp、Poly_Inv.cpp。
// ---------- 多项式除法、取模、单点求值 ----------

pair<vector<int>, vector<int>> poly_div(vector<int> a, vector<int> b) {
	shrink(a);
	shrink(b);
	int n = a.size();
	int m = b.size();
	if (n < m) {
		return {{0}, a};
	}
	auto ar = a, br = b;
	reverse(ar.begin(), ar.end());
	reverse(br.begin(), br.end());
	int len = n - m + 1;
	auto br_inv = poly_inv(br, len);
	auto qr = ar * br_inv;
	qr.resize(len);
	reverse(qr.begin(), qr.end());
	auto qb = qr * b;
	auto r = a - qb;
	shrink(qr);
	shrink(r);
	return {qr, r};
}
vector<int> operator%(vector<int> a, vector<int> b) {
	return poly_div(a, b).second;
}
int eval(const vector<int> &F, int x) {
	int res = 0;
	for (int i = F.size() - 1; i >= 0; i--) {
		res = (res * x + F[i]) % mod;
	}
	return res;
}

