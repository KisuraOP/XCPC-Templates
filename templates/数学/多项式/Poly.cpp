constexpr int mod = 998244353;
constexpr int G = 3; // 原根

int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % mod) {
		if (n & 1) s = s * k % mod;
	}
	return s;
}

// ---------- 多项式乘法 (NTT) ---------- 

vector<int> rev;
vector<int> rt{0, 1};
void dft(vector<int> &a) {
	int n = a.size();
	if ((int)rev.size() != n) {
		int k = __builtin_ctz(n) - 1;
		rev.resize(n);
		for (int i = 0; i < n; i++) {
			rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
		}
	}
	for (int i = 0; i < n; i++) {
		if (rev[i] < i) {
			swap(a[i], a[rev[i]]);
		}
	}
	if ((int)rt.size() < n) {
		int k = __builtin_ctz(rt.size());
		rt.resize(n);
		while ((1 << k) < n) {
			int e = qpow(G, (mod - 1) >> (k + 1));
			for (int i = 1 << (k - 1); i < (1 << k); i++) {
				rt[2 * i] = rt[i];
				rt[2 * i + 1] = rt[i] * e % mod;
			}
			k++;
		}
	}
	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) {
			for (int j = 0; j < k; j++) {
				int u = a[i + j];
				int v = a[i + j + k] * rt[k + j] % mod;
				a[i + j] = (u + v) % mod;
				a[i + j + k] = (u - v + mod) % mod;
			}
		}
	}
}
void idft(vector<int> &a) {
	int n = a.size();
	reverse(a.begin() + 1, a.end());
	dft(a);
	int inv = qpow(n, mod - 2);
	inv = (inv + mod) % mod;
	for (int i = 0; i < n; i++) {
		a[i] *= inv;
		a[i] %= mod;
	}
}
vector<int> operator*(vector<int> a, vector<int> b) {
	int sz = 1, tot = a.size() + b.size() - 1;
	while (sz < tot) {
		sz <<= 1;
	}
	a.resize(sz);
	b.resize(sz);
	dft(a);
	dft(b);
	for (int i = 0; i < sz; i++) {
		a[i] *= b[i];
		a[i] %= mod;
	}
	idft(a);
	a.resize(tot);
	return a;
}

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
		a[i] += b[i];
		a[i] %= mod;
	}
	shrink(a);
	return a;
}
vector<int> operator-(vector<int> a, const vector<int> &b) {
	a.resize(max(a.size(), b.size()));
	for (int i = 0; i < b.size(); i++) {
		a[i] -= b[i];
		a[i] = (a[i] + mod) % mod;
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
		c[0] = (c[0] + 2) % mod;
		b = b * c;
		b.resize(k);
	}
	b.resize(n);
	return b;
}

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

// ---------- 多项式对数函数 O(NlogN) ----------

// 要求: a[0] == 1
vector<int> poly_log(vector<int> a, int n) {
	assert(!a.empty() && a[0] == 1);
	a.resize(n);
	auto deriv_a = poly_deriv(a);
	auto inv_a = poly_inv(a, n);
	auto res = deriv_a * inv_a;
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
		auto log_b = poly_log(b, k);
		vector<int> c(a.begin(), a.begin() + min((int)a.size(), k));
		c.resize(k, 0);
		for (int i = 0; i < k; ++i) {
			c[i] = (c[i] - log_b[i] + mod) % mod;
		}
		c[0] = (c[0] + 1) % mod;
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

// ---------- 多项式多点求值 O(Mlog^2M) ----------

vector<vector<int>> ptr;
void build_ptr(int p, int l, int r, const vector<int> &A) {
	if (l == r) {
		ptr[p] = {(mod - A[l]) % mod, 1};
		return ;
	}
	int mid = l + r >> 1;
	build_ptr(p << 1, l, mid, A);
	build_ptr(p << 1 | 1, mid + 1, r, A);
	ptr[p] = ptr[p << 1] * ptr[p << 1 | 1];
}
void calc_ptr(vector<int> F, int p, int l, int r, const vector<int> &A, vector<int> &res) {
	if (r - l < 64) {
		for (int i = l; i <= r; i++) {
			res[i] = eval(F, A[i]);
		}
		return ;
	}
	F = F % ptr[p];
	int mid = l + r >> 1;
	calc_ptr(F, p << 1, l, mid, A, res);
	calc_ptr(F, p << 1 | 1, mid + 1, r, A, res);
}
vector<int> multi_eval(const vector<int> &F, const vector<int> &A) {
	if (A.empty()) {
		return {};
	}
	int m = A.size();
	ptr.assign(4 * m, {});
	build_ptr(1, 0, m - 1, A);
	vector<int> res(m);
	calc_ptr(F, 1, 0, m - 1, A, res);
	return res;
}