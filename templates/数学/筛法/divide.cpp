/*
约数个数储存在 `d` 数组中。
约数和储存在 `sigma` 数组中。
*/
vector<int> prime;
vector<int> d, cnt;
vector<int> sigma, g;
void init(int n) {
	vector<bool> not_prime(n + 1);
	d.resize(n + 1);
	cnt.resize(n + 1);
	sigma.resize(n + 1);
	g.resize(n + 1);

	d[1] = 1;
	g[1] = 1;
	sigma[1] = 1;
	for (int i = 2; i <= n; i++) {
		if(!not_prime[i]) {
			prime.push_back(i);
			cnt[i] = 1;
			d[i] = 2;

			g[i] = 1 + i;
			sigma[i] = 1 + i;
		}
		for (auto j : prime) {
			if (i * j > n) {
				break;
			}
			not_prime[i * j] = true;
			if (i % j == 0) {
				cnt[i * j] = cnt[i] + 1;
				d[i * j] = d[i] / cnt[i * j] * (cnt[i * j] + 1);

				g[i * j] = g[i] * j + 1;
				sigma[i * j] = sigma[i] / g[i] * g[i * j];
				break;
			}
			cnt[i * j] = 1;
			d[i * j] = d[i] * 2;

			g[i * j] = 1 + j;
			sigma[i * j] = sigma[i] * sigma[j];
		}
	}
}