// 矩阵求逆
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
