constexpr int mod = 1e9 + 7;

int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % mod) {
		if (n & 1) s = s * k % mod;
	}
	return s;
}

vector<int> fac, invfac;
void init(int n) {
	fac.resize(n + 1);
	invfac.resize(n + 1);
	fac[0] = 1;
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i % mod;
	}
	invfac[n] = qpow(fac[n], mod - 2);
	for (int i = n - 1; i >= 0; i--) {
		invfac[i] = invfac[i + 1] * (i + 1) % mod;
	}
} 
int C(int n, int m) {
	if (n < m || m < 0) {
		return 0;
	}
	return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

// (0, 0) -> (n, m) 不越过 y = x + a, y = x + b
int solve(int n, int m, int a, int b) {
	int u = max(a, b) + 1, v = min(a, b) - 1; // 越过
	// int u = max(a, b), v = min(a, b); // 触碰	
	if (v >= 0 || u <= 0 || m >= n + u || m <= n + v) {
		return 0;
	}
	int ans = C(n + m, n);
	auto dfs = [&](auto self, int x, int y, int t, int l1, int l2) -> int {
		int l = (t & 1) ? l1 : l2;
		int nx = y - l, ny = x + l;
		if (n - nx < 0 || n - nx > n + m) {
			return 0;
		}
		int cur = C(n + m, n - nx);
		int nxt = self(self, nx, ny, t + 1, l1, l2);
		if (t & 1) {
			return (mod - cur + nxt) % mod;
		} else {
			return (cur + nxt) % mod;
		}
	};
	ans = (ans + dfs(dfs, 0, 0, 1, u, v)) % mod;
	ans = (ans + dfs(dfs, 0, 0, 1, v, u)) % mod;
	return ans;
}