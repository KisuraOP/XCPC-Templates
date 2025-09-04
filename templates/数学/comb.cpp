for (int i = 0; i <= n; i++) {
	for (int j = 0; j <= i; j++) {
		if (j == 0 || j == i) {
			C[i][j] = 1;
		} else {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
}

constexpr int mod = 998244353;

int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % modp) {
		if (n & 1) s = s * k % modp;
	}
	return s;
}

struct math {
	int size = 0;
	vector<int> fac, inv;
	math(int n = 0) {
		init(n);
	}
	void init(int n) {
		fac.resize(n + 2);
		inv.resize(n + 2);
		fac[0] = 1;
		for (int i = size + 1; i <= n; i++) {
			fac[i] = fac[i - 1] * i % mod;
		}
		inv[n] = qpow(fac[n], mod - 2);
		for (int i = n; i >= size + 1; i--) {
			inv[i - 1] = inv[i] * i % mod;
		}
		size = n;
	}
	int C(int n, int m) {
		if (n < m || m < 0) return 0;
		if (n > size) init(n);
		return fac[n] * inv[m] % mod * inv[n - m] % mod;
	}
} binom;

int C(int n, int m) {
	return binom.C(n, m); 
}
int fac(int n) {
	if (binom.size < n) binom.init(n);
	return binom.fac[n];
}
int invfac(int n) {
	if (binom.size < n) binom.init(n);
	return binom.inv[n];
}
int bfC(int n, int m) {
	if (n < m || m < 0) return 0;
	int s = 1;
	for (int i = n - m + 1; i <= n; i++) {
		s = s * i % mod;
	}
	return s * qpow(fac(m), mod - 2) % mod;
}