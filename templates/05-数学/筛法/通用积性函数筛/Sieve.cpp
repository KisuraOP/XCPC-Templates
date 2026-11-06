/*
auto f = sieve(n, calc);
返回积性函数 f 在 [1, n] 的值，f[1] = 1。

calc(p, k, q, v) 返回 f(p^k)。
p 为质数，q = p^k，v = f(p^(k-1))。

calc 为 O(1) 时，时间复杂度 O(n)。
*/
template<class F>
vector<int> sieve(int n, F calc) {
	vector<int> pri, pw(n + 1), cnt(n + 1, 1), f(n + 1);
	f[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!pw[i]) {
			pri.push_back(i);
			pw[i] = i;
			f[i] = calc(i, 1, i, 1);
		}
		for (int p : pri) {
			int x = i * p;
			if (x > n) {
				break;
			}
			if (i % p == 0) {
				pw[x] = pw[i] * p;
				cnt[x] = cnt[i] + 1;
				f[x] = f[i / pw[i]] * calc(p, cnt[x], pw[x], f[pw[i]]);
				break;
			}
			pw[x] = p;
			f[x] = f[i] * f[p];
		}
	}
	return f;
}
