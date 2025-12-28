vector<int> phi, mu;
vector<int> prime;
vector<int> minp;
void init_phi(int n) {
	vector<bool> not_prime(n + 1);
	phi.resize(n + 1);
	mu.resize(n + 1);
    minp.resize(n + 1);
	phi[1] = mu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if(!not_prime[i]) {
			prime.push_back(i);
			phi[i] = i - 1;
			mu[i] = -1;
            minp[i] = i;
		}
		for (auto j : prime) {
			if (i * j > n) {
				break;
			}
			not_prime[i * j] = true;
            minp[i * j] = j;
			if (i % j == 0) {
				phi[i * j] = phi[i] * j;
				mu[i * j] = 0;
				break;
			}
			phi[i * j] = phi[i] * phi[j];
			mu[i * j] = -mu[i];
		}
	}
}