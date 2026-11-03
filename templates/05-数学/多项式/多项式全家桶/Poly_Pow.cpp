// 依赖 Poly_Mul.cpp、Poly_Base.cpp、Poly_Log.cpp、Poly_Exp.cpp。
// ---------- 多项式快速幂 O(NlogN) ----------

// 计算 A(x)^k mod x^n
vector<int> poly_pow(vector<int> a, int k, int n) {
	shrink(a);
    if (a.empty() || a.size() == 1 && a[0] == 0) {
        return vector<int>(n, 0);
    }
	int d = -1;
	for(int i = 0; i < a.size(); i++) {
		if (a[i] != 0) {
			d = i;
			break;
		}
	}
	if (d == -1 || d * k >= n) {
		return vector<int>(n, 0);
	}
	int c = a[d];
	int c_inv = qpow(c, mod - 2);
	vector<int> ap(a.size() - d);
	for(int i = 0; i < ap.size(); i++) {
		ap[i] = a[i + d] * c_inv % mod;
	}
	ap = poly_log(ap, n);
	for(auto &x : ap) {
		x = x * k % mod;
	}
	ap = poly_exp(ap, n);
	int ck = qpow(c, k);
	vector<int> res(n, 0);
	for(int i = 0; i + d * k < n && i < ap.size(); i++) {
		res[i + d * k] = ap[i] * ck % mod;
	}
	return res;
}

