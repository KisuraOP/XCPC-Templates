constexpr int mod = 998244353;

int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % mod) {
		if (n & 1) {
			s = s * k % mod;
		}
	}
	return s;
}

using mat = vector<vector<int>>;

// 求一个矩阵的特征多项式, 即 res[i] = [x^i] det(xI - a)
// https://www.luogu.com.cn/problem/P7776
// O(n^3)
vector<int> charpoly(mat a) {
	int n = a.size();
	for (int i = 1; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (a[j][i - 1]) {
				swap(a[i], a[j]);
				for (int k = 0; k < n; k++) {
					swap(a[k][i], a[k][j]);
				}
				break;
			}
		}
		if (!a[i][i - 1]) {
			continue;
		}
		int x = a[i][i - 1];
		int inv = qpow(x, mod - 2);
		for (int j = 0; j < n; j++) {
			a[j][i] = a[j][i] * x % mod;
		}
		for (int j = i - 1; j < n; j++) {
			a[i][j] = a[i][j] * inv % mod;
		}
		for (int j = i + 1; j < n; j++) {
			int z = a[j][i - 1];
			int iz = mod - z;
			for (int k = 0; k < n; k++) {
				a[k][i] = (a[k][i] + a[k][j] * z) % mod;
			}
			for (int k = i - 1; k < n; k++) {
				a[j][k] = (a[j][k] + a[i][k] * iz) % mod;
			}
		}
	}
	mat dp(n + 1, vector<int>(n + 1));
	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		int x = 1;
		for (int j = i; j >= 0; j--) {
			int y = (mod - x) * a[j][i] % mod;
			for (int k = 0; k <= j; k++) {
				dp[i + 1][k] = (dp[i + 1][k] + y * dp[j][k]) % mod;
			}
			if (j) {
				x = x * a[j][j - 1] % mod;
			}
		}
		for (int k = 0; k <= i; k++) {
			dp[i + 1][k + 1] = (dp[i + 1][k + 1] + dp[i][k]) % mod;
		}
	}
	return dp[n];
}

