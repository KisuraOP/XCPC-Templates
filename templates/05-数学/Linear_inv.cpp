vector<int> inv(n + 1);
inv[1] = 1;
for (int i = 2; i <= n; i++) {
	inv[i] = (-inv[mod % i] * (mod / i) % mod + mod) % mod;
}