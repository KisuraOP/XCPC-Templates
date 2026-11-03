// 依赖 Poly_Mul.cpp。
// ---------- 多项式加减、求导、积分 ----------

void shrink(vector<int> &a) {
	while (a.size() > 1 && a.back() == 0) {
		a.pop_back();
	}
	if (a.empty()) {
		a.push_back(0);
	}
}
vector<int> operator+(vector<int> a, const vector<int> &b) {
	a.resize(max(a.size(), b.size()));
	for (int i = 0; i < b.size(); i++) {
		a[i] = (a[i] + b[i]) % mod;
	}
	shrink(a);
	return a;
}
vector<int> operator-(vector<int> a, const vector<int> &b) {
	a.resize(max(a.size(), b.size()));
	for (int i = 0; i < b.size(); i++) {
		a[i] -= b[i];
		if (a[i] < 0) {
			a[i] += mod;
		}
	}
	shrink(a);
	return a;
}
vector<int> poly_deriv(vector<int> a) {
	if (a.empty()) {
		return {};
	}
	for (int i = 0; i + 1 < a.size(); i++) {
		a[i] = a[i + 1] * (i + 1) % mod;
	}
	a.pop_back();
	shrink(a);
	return a;
}
vector<int> invt;
void pre_inv(int n) {
    if (invt.empty()) {
        invt.resize(2);
        invt[1] = 1;
    }
    int sz = invt.size();
    if (n <= sz) {
    	return;
    }
    invt.resize(n);
    for (int i = sz; i < n; i++) {
        invt[i] = (mod - invt[mod % i] * (mod / i) % mod) % mod;
    }
}
vector<int> poly_integral(vector<int> a) {
	if (a.empty()) {
		return {};
	}
    int n = a.size();
    pre_inv(n + 1);
	a.push_back(0);
	for (int i = n; i > 0; i--) {
		a[i] = a[i - 1] * invt[i] % mod;
	}
	a[0] = 0;
	shrink(a);
	return a;
}

