// 依赖 Poly_Mul.cpp。
// ---------- 多项式求逆 (牛顿迭代法) ----------

vector<int> poly_inv(const vector<int> &a, int n) {
	if (n == 0) {
		return {};
	}
	vector<int> b = {qpow(a[0], mod - 2)};
	int k = 1;
	while (k < n) {
		k <<= 1;
		vector<int> c(a.begin(), a.begin() + min((int)a.size(), k));
		c = c * b;
		c.resize(k);
		for (auto &x : c) {
			x = mod - x;
		}
		c[0] += 2;
		if (c[0] >= mod) {
			c[0] -= mod;
		}
		b = b * c;
		b.resize(k);
	}
	b.resize(n);
	return b;
}

