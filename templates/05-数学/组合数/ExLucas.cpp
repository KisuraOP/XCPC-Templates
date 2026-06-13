int qpow(int k, int n, int p) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % p) {
		if (n & 1) s = s * k % p;
	}
	return s;
}
void exgcd(int a, int b, int &d, int &x, int &y) {
	if (!b) {
		d = a;
		x = 1;
		y = 0;
	} else {
		exgcd(b, a % b, d, y, x);
		y -= x * (a / b);
	}
}
int inv(int a, int p) {
	int d, x, y;
	exgcd(a, p, d, x, y);
	return (x % p + p) % p;
} 

struct ExLucas {
	int fac(int x, int pi, int pk) {
		if (x == 0) {
			return 1ll;
		}
		int res = 1;
		for (int i = 1; i <= pk; i++) {
			if (i % pi != 0) {
				res = res * i % pk;
			}
		}
		res = qpow(res, x / pk, pk);
		for (int i = 1; i <= x % pk; i++) {
			if (i % pi != 0) {
				res = res * i % pk;
			}
		}
		return res * fac(x / pi, pi, pk) % pk;
	}
	int get(int x, int pi) {
		if (x == 0) {
			return 0ll;
		}
		return x / pi + get(x / pi, pi);
	}
	int C(int n, int m, int pi, int pk) {
		if (n < m) {
			return 0ll;
		}
		int k = get(n, pi) - get(m, pi) - get(n - m, pi);
		int a = fac(n, pi, pk);
		int b = fac(m, pi, pk);
		int c = fac(n - m, pi, pk);
		return a * inv(b, pk) % pk * inv(c, pk) % pk * qpow(pi, k, pk) % pk;
	}
	int C(int n, int m, int mod) {
		int t = mod;
		vector<array<int, 2>> f;
		for (int i = 2; i * i <= t; i++) {
			if (t % i == 0) {
				int pk = 1;
				while (t % i == 0) {
					pk *= i;
					t /= i;
				}
				f.push_back({i, pk});
			}
		}
		if (t > 1) {
			f.push_back({t, t});
		}
		int ans = 0;
		for (auto [p, pk] : f) {
			int a = C(n, m, p, pk);
			int mi = mod / pk;
			ans = (ans + a * mi % mod * inv(mi, pk) % mod) % mod;
		}
		return ans;
	}
} binom;