struct matrix {
	int n, m;
	vector<vector<int>> a;
	matrix(int n) : n(n), m(n), a(n, vector<int>(n, 0)) {}
	matrix(int n, int m) : n(n), m(m), a(n, vector<int>(m, 0)) {}
	matrix(int n, int m, int k) : n(n), m(m), a(n, vector<int>(m, k)) {}
	void read() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> a[i][j];
			}
		}
	}
	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << a[i][j] << " \n"[j == m - 1];
			}
		}
	}
	void build() {
		for (int i = 0; i < min(n, m); i++) {
			a[i][i] = 1;
		}
	}
	matrix tp() {
		matrix z(m, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				z.a[j][i] = a[i][j];
			}
		}
		return z;
	}
};
constexpr int mod = 1e9 + 7;
matrix operator * (const matrix &x, const matrix &y) {
	assert(x.m == y.n);
	matrix z(x.n, y.m);
	for (int i = 0; i < x.n; i++) {
		for (int k = 0; k < x.m; k++) {
			if (x.a[i][k] == 0) {
				continue;
			}
			for (int j = 0; j < y.m; j++) {
				z.a[i][j] = (z.a[i][j] + x.a[i][k] * y.a[k][j]) % mod;
			}
		}
	}
	return z;
}
matrix qpow(matrix a, int k) {
	assert(a.n == a.m);
	matrix z(a.n);
	z.build();
	for ( ; k; k >>= 1, a = a * a) {
		if (k & 1) z = z * a;
	}
	return z;
}
int det(matrix p) {
	assert(p.n == p.m);
	int n = p.n;
	int ans = 1, tmp = 1;
	auto a = p.a;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			while (a[i][i]) {
				int d = a[j][i] / a[i][i];
				for (int k = i; k < n; k++) {
					a[j][k] = (a[j][k] - d * a[i][k] % mod + mod) % mod;
				}
				swap(a[i], a[j]);
				tmp = -tmp;
			}
			swap(a[i], a[j]);
			tmp = -tmp;
		}
	}
	for (int i = 0; i < n; i++) {
		ans = ans * a[i][i] % mod;
	}
	ans = ans * tmp % mod;
	return (ans % mod + mod) % mod;
}