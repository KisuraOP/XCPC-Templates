// 1-index
struct SparseTable {
	int n;
	vector<vector<int>> ST;
	SparseTable(vector<int> &arr) {
		this->n = arr.size() - 1;
		ST.resize(n + 1 ,vector<int>(__lg(n) + 1));
		for (int i = 1; i <= n; i++) {
			ST[i][0] = arr[i];
		}
		for (int j = 1; j <= __lg(n); j++) {
			for (int i = 1; i + (1LL << j) - 1 <= n; i++) {
				ST[i][j] = max(ST[i][j - 1], ST[i + (1LL << (j - 1))][j - 1]);
			}
		}
	}
	int query(int l, int r) {
		int len = __lg(r - l + 1);
		return max(ST[l][len], ST[r - (1LL << len) + 1][len]);
	}
};