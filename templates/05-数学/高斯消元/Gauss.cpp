/*
vector<double> ans = gauss(ori);
ori 为增广矩阵，返回解向量。
若无解，会输出 "No Solution"；若多解，会输出 "Many Solution"
*/

// 浮点数版本
constexpr double eps = 1e-8;
vector<double> gauss(vector<vector<int>> &ori) {
	int n = ori.size();
	vector a(n, vector<double>(n + 1));
	vector<double> ans(n, inf);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++) {
			a[i][j] = 1.0 * ori[i][j];
		}
	}
	int r = 0;
	for (int c = 0; c < n; c++) {
		for (int i = r + 1; i < n; i++) {
			if (fabs(a[i][c]) > fabs(a[r][c])) {
				swap(a[r], a[i]);
			}
		}
		if (fabs(a[r][c]) < eps) {
			continue;
		}
		for (int i = n; i >= c; i--) {
			a[r][i] /= a[r][c];
		}
		for (int i = r + 1; i < n; i++) {
			for (int j = n; j >= c; j--) {
				a[i][j] -= a[i][c] * a[r][j];
			}
		}
		r++;
	}
	if (r < n) {
		for (int i = r; i < n; i++) {
			if (fabs(a[i][n]) > eps) {
				cout << "No Solution\n";
				return ans;
			}
		}
		cout << "Many Solution\n";
		return ans;
	}
	for (int j = n - 1; j > 0; j--) {
		for (int i = 0; i < j; i++) {
			a[i][n] -= a[j][n] * a[i][j];
			a[i][j] -= a[j][j] * a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		ans[i] = a[i][n];
	}
	return ans;
}


// 模意义版本
constexpr int mod = 1e9 + 7;
int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % mod) {
		if (n & 1) s = s * k % mod;
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


// 矩阵求逆
constexpr int mod = 1e9 + 7;
int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % mod) {
		if (n & 1) s = s * k % mod;
	}
	return s;
}
vector<vector<int>> matrix_inverse(vector<vector<int>> &a) {
    int n = a.size();
    vector<vector<int>> b(n, vector<int>(2 * n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = (a[i][j] % mod + mod) % mod;
        }
        b[i][n + i] = 1;
    }
    int r = 0;
    for (int c = 0; c < n; c++) {
        int pv = r;
        for (int i = r + 1; i < n; i++) {
            if (b[i][c] > b[pv][c]) {
                pv = i;
            }
        }
        if (pv != r) {
            swap(b[r], b[pv]);
        }
        if (b[r][c] == 0) {
            // cout << "No Inverse\n";
            return vector<vector<int>>();
        }
        int inv = qpow(b[r][c], mod - 2);
        for (int j = c; j < 2 * n; j++) {
            b[r][j] = b[r][j] * inv % mod;
        }
        for (int i = 0; i < n; i++) {
            if (i != r && b[i][c] != 0) {
                int f = b[i][c];
                for (int j = c; j < 2 * n; j++) {
                    b[i][j] = (b[i][j] - f * b[r][j] % mod + mod) % mod;
                }
            }
        }
        r++;
    }
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = b[i][n + j];
        }
    }
    return ans;
}