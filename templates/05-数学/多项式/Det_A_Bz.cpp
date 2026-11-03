// 依赖 Charpoly.cpp。
// 求 ans[k] = [z^k] det(a + bz)
// https://qoj.ac/contest/3936/problem/59
// O(n^3)
vector<int> det_a_plus_bz(mat a, mat b) {
	int n = a.size();
	vector<int> ans(n + 1);
	int t = 1, d = 0;
	for (int i = 0; i < n; i++) {
		for ( ; !b[i][i]; ) {
			for (int j = i + 1; j < n; j++) {
				if (b[i][j]) {
					t = mod - t;
					for (int k = 0; k < n; k++) {
						swap(a[k][i], a[k][j]);
						swap(b[k][i], b[k][j]);
					}
					break;
				}
			}
			if (b[i][i]) {
				break;
			}
			if (++d > n) {
				return ans;
			}
			for (int j = 0; j < n; j++) {
				b[i][j] = a[i][j];
				a[i][j] = 0;
			}
			for (int j = 0; j < i; j++) {
				int c = mod - b[i][j];
				for (int k = 0; k < n; k++) {
					a[i][k] = (a[i][k] + c * a[j][k]) % mod;
					b[i][k] = (b[i][k] + c * b[j][k]) % mod;
				}
			}
		}
		t = t * b[i][i] % mod;
		int inv = qpow(b[i][i], mod - 2);
		for (int j = 0; j < n; j++) {
			a[i][j] = a[i][j] * inv % mod;
			b[i][j] = b[i][j] * inv % mod;
		}
		for (int j = 0; j < n; j++) {
			if (j == i) {
				continue;
			}
			int c = mod - b[j][i];
			for (int k = 0; k < n; k++) {
				a[j][k] = (a[j][k] + c * a[i][k]) % mod;
				b[j][k] = (b[j][k] + c * b[i][k]) % mod;
			}
		}
	}
	auto r = charpoly(a);
	for (int i = d; i <= n; i++) {
		ans[i - d] = ((n - i) & 1 ? mod - t : t) * r[i] % mod;
	}
	return ans;
}
