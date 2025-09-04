int Lucas(int n, int m, int p) {
	if (m == 0) return 1LL;
	return Lucas(n / p, m / p, p) * C(n % p, m % p, p) % p;
}