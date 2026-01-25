/*
检验 long long 范围内的质数。
时间复杂度 O(|A| \log n), 如下代码中 |A| = 8。
*/

int mul(int a, int b, int m) {
	return (__int128)a * b % m;
}
int qpow(int a, int b, int m) {
	int res = 1;
	for ( ; b; b >>= 1, a = mul(a, a, m)) {
		if (b & 1) {
			res = mul(res, a, m);
		}
	}
	return res;
}
int A[] = {2, 3, 5, 7, 11, 13, 17, 37};
bool isprime(int n) {
	if (n < 2) {
		return false;
	}
	int s = __builtin_ctzll(n - 1);
	int d = (n - 1) >> s;
	for (auto a : A) {
		if (a == n) {
			return true;
		}
		int x = qpow(a, d, n);
		if (x == 1 || x == n - 1) {
			continue;
		}
		bool ok = false;
		for (int i = 0; i < s - 1; i++) {
			x = mul(x, x, n);
			if (x == n - 1) {
				ok = true;
				break;
			}
		}
		if (!ok) {
			return false;
		}
	}
	return true;
}