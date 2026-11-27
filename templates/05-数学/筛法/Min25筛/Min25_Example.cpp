/*
依赖 Min25.cpp。

phi2(n);
返回 sum_{i=1}^n phi(i)^2。
*/
int phi2(int n) {
	Min25 t(n);
	auto a = t.prime([](int x) {
		return 1;
	}, [](int x) {
		return x % mod;
	});
	auto b = t.prime([](int x) {
		return x % mod;
	}, [](int x) {
		return (__int128)x * (x + 1) / 2 % mod;
	});
	auto c = t.prime([](int x) {
		return (__int128)x * x % mod;
	}, [](int x) {
		return (__int128)x * (x + 1) * (2 * x + 1) / 6 % mod;
	});
	for (int i = 1; i < c.size(); i++) {
		c[i] = ((c[i] + a[i] - 2 * b[i]) % mod + mod) % mod;
	}
	return t.sum(move(c), [](int p, int k, int q, int v) {
		int x = (p - 1) % mod, y = p % mod;
		return k == 1 ? x * x % mod : v * y % mod * y % mod;
	});
}
