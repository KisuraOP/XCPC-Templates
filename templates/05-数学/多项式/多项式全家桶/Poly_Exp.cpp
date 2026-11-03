// 依赖 Poly_Mul.cpp、Poly_Log.cpp。
// ---------- 多项式指数函数 O(NlogN) ----------

// 要求: a[0] == 0
vector<int> poly_exp(vector<int> a, int n) {
	assert(a.empty() || a[0] == 0);
	if (n == 0) {
		return {};
	}
	vector<int> b = {1};
	a.resize(n);
	int k = 1;
	while (k < n) {
		k <<= 1;
		auto lb = poly_log(b, k);
		vector<int> c(a.begin(), a.begin() + min((int)a.size(), k));
		c.resize(k, 0);
		for (int i = 0; i < k; ++i) {
			c[i] -= lb[i];
			if (c[i] < 0) {
				c[i] += mod;
			}
		}
		c[0] += 1;
		if (c[0] >= mod) {
			c[0] -= mod;
		}
		b = b * c;
		b.resize(k);
	}
	b.resize(n);
	return b;
}

