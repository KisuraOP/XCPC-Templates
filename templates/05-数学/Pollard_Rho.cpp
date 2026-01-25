/*
期望时间复杂度: O(n^{1/4})
fac(n) 获取 n 的质因子集合。
*/

// 先在这里完整抄写上一篇的 Miller-Rabin

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int pollard_rho(int n) {
	int c = rng() % (n - 1) + 1;
	int s = 0, t = 0;
	for (int g = 1; ; g <<= 1, s = t)   {
		int v = 1;
		for (int st = 1; st <= g; st++) {
			t = (mul(t, t, n) + c) % n;
			v = mul(v, abs(s - t), n);
			if (st % 127 == 0) {
				int d = __gcd(v, n);
				if (d > 1) {
					return d;
				}
			}
		}
		int d = __gcd(v, n);
		if (d > 1) {
			return d;
		}
	}
}
vector<int> _fac(int x) {
	if (x < 2) {
		return {};
	}
	if (isprime(x)) {
		return {x};
	}
	int p = x;
	while (p >= x) {
		p = pollard_rho(x);
	}
	while (x % p == 0) {
		x /= p;
	}
	auto s = _fac(x), t = _fac(p);
	s.insert(s.end(), t.begin(), t.end());
	return s;
}
vector<int> fac(int x) {
	auto s = _fac(x);
	sort(s.begin(), s.end());
	s.erase(unique(s.begin(), s.end()), s.end());
	return s;
}