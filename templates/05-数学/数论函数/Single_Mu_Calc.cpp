int getmu(int n) {
	int ans = 1;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans = -ans;
			n /= i;
			if (n % i == 0) {
				return 0;
			}
		}
	}
	if (n != 1) {
		ans = -ans;
	}
	return ans;
}