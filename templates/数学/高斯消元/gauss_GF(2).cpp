/*
GF(2)+bitset 高斯消元 O(n^3 / w)

x ^ y = 1
x      = 0
vector<vector<int>> mat = {
    {1,1,1}, // x + y = 1
    {1,0,0}  // x     = 0
};
Node res = gauss(mat, 2); // 2 个变量
*/

const int N = 1024; // 最大列数 (变量数+1)
struct Node {
	int rk; // 秩
	int free; // 自由变元数，大于 0 -> 多解
	bool ok; // ok = 0 无解
	vector<int> sol; // 若有解，返回一组解
};

Node gauss(vector<vector<int>> &ori, int m) {
	int n = ori.size();
	vector<bitset<N>> a(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			if (ori[i][j]) a[i][j] = 1;
		}
	}
	vector<int> wh(m, -1);
	int r = 0;
	for (int c = 0; c < m && r < n; c++) {
		int p = r;
		while (p < n && !a[p][c]) {
			p++;
		}
		if (p == n) {
			continue;
		}
		swap(a[r], a[p]);
		wh[c] = r;
		for (int i = 0; i < n; i++) {
			if (i != r && a[i][c]) {
				a[i] ^= a[r];
			}
		}
		r++;
	}
	for (int i = 0; i < n; i++) {
		bool all0 = true;
		for (int j = 0; j < m; j++) {
			if (a[i][j]) { 
				all0 = false; 
				break; 
			}
		}
		if (all0 && a[i][m]) {
			return {r, m - r, false, {}};
		}
	}
	vector<int> x(m, 0);
	for (int c = m - 1; c >= 0; c--) {
		if (wh[c] != -1) {
			int v = a[wh[c]][m];
			for (int j = c + 1; j < m; j++) {
				if (a[wh[c]][j]) {
					v ^= x[j];
				}
			}
			x[c] = v;
		}
	}
	return {r, m - r, true, x};
}