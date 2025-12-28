// \sum_{0}^{n - 1} floor( (a * i + b) / m )
// O(log m)
int floor_sum(int n, int m, int a, int b) {
	int ans = 0;
	if (a < 0) {
		int a2 = (a % m + m) % m;
		ans -= n * (n - 1) / 2 * ((a2 - a) / m);
		a = a2;
	}
	if (b < 0) {
		int b2 = (b % m + m) % m;
		ans -= n * ((b2 - b) / m);
		b = b2;
	}
	while (true) {
		if (a >= m) {
			ans += n * (n - 1) / 2 * (a / m);
			a %= m;
		}
		if (b >= m) {
			ans += n * (b / m);
			b %= m;
		}
		int ymax = a * n + b;
		if (ymax < m) {
			break;
		}
		n = ymax / m;
		b = ymax % m;
		swap(m, a);
	}
	return ans;
}