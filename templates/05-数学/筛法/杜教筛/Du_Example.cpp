/*
依赖 Du.cpp 和 ../通用积性函数筛/Sieve.cpp。

auto [phi, mu] = du(n, b);
返回欧拉函数、莫比乌斯函数在 [1, n] 的和，预筛上界为 b。
*/
array<int, 2> du(int n, int b) {
	auto phi = sieve(b, [](int p, int k, int q, int v) {
		return k == 1 ? p - 1 : v * p;
	});
	auto mu = sieve(b, [](int p, int k, int q, int v) {
		return k == 1 ? -1 : 0;
	});
	for (int i = 1; i <= b; i++) {
		phi[i] += phi[i - 1];
		mu[i] += mu[i - 1];
	}
	auto g = [](int x) {
		return x;
	};
	Du a(move(phi), g, [](int x) {
		return x * (x + 1) / 2;
	});
	Du c(move(mu), g, [](int x) {
		return 1;
	});
	return {a.sum(n), c.sum(n)};
}
