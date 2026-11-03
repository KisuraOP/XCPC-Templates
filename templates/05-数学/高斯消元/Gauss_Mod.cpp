// 模意义版本
constexpr int mod = 1e9 + 7;
int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % mod) {
		if (n & 1) {
			s = s * k % mod;
		}
	}
	return s;
}
vector<int> gauss(vector<vector<int>> &a) {
	int n = a.size();
	vector<int> ans(n, -1);
	int r = 0;
	for (int c = 0; c < n; c++) {
		for (int i = r + 1; i < n; i++) {
			if (a[i][c] > a[r][c]) {
				swap(a[r], a[i]);
			}
		}
		if (a[r][c] == 0) {
			continue;
		}
		int inv = qpow(a[r][c], mod - 2);
		for (int i = n; i >= c; i--) {
			a[r][i] = a[r][i] * inv % mod;
		}
		for (int i = r + 1; i < n; i++) {
			for (int j = n; j >= c; j--) {
				a[i][j] = (a[i][j] - a[i][c] * a[r][j] % mod + mod) % mod;
			}
		}
		r++;
	}
	if (r < n) {
		for (int i = r; i < n; i++) {
			if (a[i][n]) {
				cout << "No Solution\n";
				return ans;
			}
		}
		cout << "Many Solution\n";
		return ans;
	}
	for (int j = n - 1; j > 0; j--) {
		for (int i = 0; i < j; i++) {
			a[i][n] = (a[i][n] - a[j][n] * a[i][j] % mod + mod) % mod;
			a[i][j] = (a[i][j] - a[j][j] * a[i][j] % mod + mod) % mod;
		}
	}
	for (int i = 0; i < n; i++) {
		ans[i] = a[i][n];
	}
	return ans;
}


