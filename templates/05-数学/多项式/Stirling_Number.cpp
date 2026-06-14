constexpr int mod = 998244353;
constexpr int G = 3; // 原根

constexpr int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % mod) {
		if (n & 1) s = s * k % mod;
	}
	return s;
}
vector<int> fac, invfac, inv;
void init(int n) {
	int sz = fac.size();
	if (sz > n) return ;
	fac.resize(n + 1);
	invfac.resize(n + 1);
	inv.resize(n + 1);
	if (sz == 0) {
		fac[0] = invfac[0] = 1;
		sz = 1;
	}
	for (int i = sz; i <= n; i++) {
		fac[i] = fac[i - 1] * i % mod;
	}
	invfac[n] = qpow(fac[n], mod - 2);
	for (int i = n - 1; i >= sz; i--) {
		invfac[i] = invfac[i + 1] * (i + 1) % mod;
	}
	for (int i = sz; i <= n; i++) {
		inv[i] = invfac[i] * fac[i - 1] % mod;
	}
}

// ---------- 多项式乘法 (NTT) ---------- 

const int Ginv = qpow(G, mod - 2);
vector<int> rt = {0, 1}, irt = {0, 1};

void init_rt(int n) {
	int sz = rt.size();
	if (sz >= n) return;
	while (sz < n) sz <<= 1;
	rt.resize(sz);
	irt.resize(sz);
	for (int k = 2; k < sz; k <<= 1) {
		int z = qpow(G, (mod - 1) / (2 * k));
		int iz = qpow(Ginv, (mod - 1) / (2 * k));
		for (int j = 0; j < k; j += 2) {
			rt[k + j] = rt[(k >> 1) + (j >> 1)];
			rt[k + j + 1] = rt[k + j] * z % mod;
			irt[k + j] = irt[(k >> 1) + (j >> 1)];
			irt[k + j + 1] = irt[k + j] * iz % mod;
		}
	}
}
void dft(vector<int> &a) {
	int n = a.size();
	if (rt.size() < n) init_rt(n);
	for (int k = n >> 1; k > 0; k >>= 1) {
		for (int i = 0; i < n; i += 2 * k) {
			const int* w = &rt[k]; 
			for (int j = 0; j < k; j++) {
				int u = a[i + j];
				int v = a[i + j + k];
				int s = u + v, t = u - v;
				a[i + j] = (s >= mod ? s - mod : s);
				a[i + j + k] = (t < 0 ? t + mod : t) * w[j] % mod;
			}
		}
	}
}
void idft(vector<int> &a) {
	int n = a.size();
	for (int k = 1; k < n; k <<= 1) {
		for (int i = 0; i < n; i += 2 * k) {
			const int* w = &irt[k];
			for (int j = 0; j < k; j++) {
				int u = a[i + j];
				int v = a[i + j + k] * w[j] % mod;
				int s = u + v, t = u - v;
				a[i + j] = (s >= mod ? s - mod : s);
				a[i + j + k] = (t < 0 ? t + mod : t);
			}
		}
	}
	int inv_val = qpow(n, mod - 2);
	for (int i = 0; i < n; i++) {
		a[i] = a[i] * inv_val % mod;
	}
}
vector<int> operator*(vector<int> a, vector<int> b) {
	int sz = 1, n = a.size() + b.size() - 1;
	while (sz < n) sz <<= 1;
	a.resize(sz);
	b.resize(sz);
	dft(a);
	dft(b);
	for (int i = 0; i < sz; i++) {
		a[i] = a[i] * b[i] % mod;
	}
	idft(a);
	a.resize(n);
	return a;
}

// ---------- 多项式求导、积分 ----------

void shrink(vector<int> &a) {
	while (a.size() > 1 && a.back() == 0) {
		a.pop_back();
	}
	if (a.empty()) {
		a.push_back(0);
	}
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
vector<int> poly_shift(const vector<int> &A, int c) {
	int d = A.size() - 1;
	if (d < 0) return {};
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

// ---------- 多项式对数函数 O(NlogN) ----------

// 要求: a[0] == 1
vector<int> poly_log(vector<int> a, int n) {
	assert(!a.empty() && a[0] == 1);
	a.resize(n);
	auto res = poly_deriv(a) * poly_inv(a, n);
	res.resize(n);
	res = poly_integral(res);
	res.resize(n);
	return res;
}

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

// ---------- 多项式快速幂 O(NlogN) ----------

// 计算 A(x)^k mod x^n
vector<int> poly_pow(vector<int> a, int k, int n) {
	shrink(a);
	if (a.empty() || (a.size() == 1 && a[0] == 0)) {
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

// 同一行第二类斯特林数 O(N log N)
// {S(n, 0), S(n, 1), ..., S(n, n)}
vector<int> stirl2_row(int n) {
	if (n == 0) return {1};
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

// 同一列第二类斯特林数 O(N log N)
// {S(0, k), S(1, k), ..., S(n, k)}
vector<int> stirl2_col(int n, int k) {
	if (k > n) return vector<int>(n + 1, 0);
	if (k == 0) {
		vector<int> res(n + 1, 0);
		res[0] = 1;
		return res;
	}
	init(n);
	vector<int> A(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		A[i] = invfac[i];
	}
	auto B = poly_pow(A, k, n + 1);
	int inv_k = invfac[k];
	for (int i = 0; i <= n; i++) {
		B[i] = B[i] * fac[i] % mod * inv_k % mod;
	}
	return B;
}

// 同一行无符号第一类斯特林数 O(N log N)
// {s(n, 0), s(n, 1), ..., s(n, n)}
vector<int> stirl1_row(int n) {
	if (n == 0) return {1};
	int h = 0;
	while ((1LL << h) <= n) h++;
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

// 同一列无符号第一类斯特林数 O(N log N)
// {s(0, k), s(1, k), ..., s(n, k)}
vector<int> stirl1_col(int n, int k) {
	if (k > n) return vector<int>(n + 1, 0);
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
