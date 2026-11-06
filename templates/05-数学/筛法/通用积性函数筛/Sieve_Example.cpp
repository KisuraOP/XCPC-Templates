/*
依赖 Sieve.cpp，四种函数按需选用。
phi、mu、d、sigma 分别为欧拉函数、莫比乌斯函数、约数个数、约数和。
*/
vector<int> phi, mu, d, sigma;
void init(int n) {
	phi = sieve(n, [](int p, int k, int q, int v) {
		return k == 1 ? p - 1 : v * p;
	});
	mu = sieve(n, [](int p, int k, int q, int v) {
		return k == 1 ? -1 : 0;
	});
	d = sieve(n, [](int p, int k, int q, int v) {
		return k + 1;
	});
	sigma = sieve(n, [](int p, int k, int q, int v) {
		return v + q;
	});
}
