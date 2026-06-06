constexpr int mod = 998244353;
int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % mod) {
		if (n & 1) s = s * k % mod;
	}
	return s;
}
vector<int> interpolate(const vector<array<int, 2>> &p) {
	int n = p.size();
	vector<int> a(n + 1), c(n);
	a[0] = 1;
	for (auto [x, y] : p) {
		for (int i = n; i > 0; i--) {
			a[i] = (a[i - 1] + (mod - x) * a[i]) % mod;
		}
		a[0] = a[0] * (mod - x) % mod;
	}
	for (auto [x, y] : p) {
		int t = 1, q = 0;
		for (auto [xj, yj] : p) {
			if (x != xj) {
				t = t * (x - xj + mod) % mod;
			}
		}
		int w = y * qpow(t, mod - 2) % mod;
		for (int j = n - 1; j >= 0; j--) {
			q = (a[j + 1] + x * q) % mod;
			c[j] = (c[j] + w * q) % mod;
		}
	}
	return c;
}
int eval(const vector<int> &F, int x) {
	int res = 0;
	for (int i = F.size() - 1; i >= 0; i--) {
		res = (res * x + F[i]) % mod;
	}
	return res;
}