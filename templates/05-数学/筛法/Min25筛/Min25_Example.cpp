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
		return x;
	});
	auto b = t.prime([](int x) {
		return x;
	}, [](int x) {
		return x * (x + 1) / 2;
	});
	auto c = t.prime([](int x) {
		return x * x;
	}, [](int x) {
		return x * (x + 1) * (2 * x + 1) / 6;
	});
	for (int i = 1; i < c.size(); i++) {
		c[i] += a[i] - 2 * b[i];
	}
	return t.sum(move(c), [](int p, int k, int q, int v) {
		return k == 1 ? (p - 1) * (p - 1) : v * p * p;
	});
}
