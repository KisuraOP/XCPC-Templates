// 1-index
struct SparseTable {
	int n;
	vector<vector<int>> ST;
	SparseTable(vector<int> &arr) {
		this->n = arr.size() - 1;
		ST.resize(__lg(n) + 1 ,vector<int>(n + 1));
		for (int i = 1; i <= n; i++) {
			ST[0][i] = arr[i];
		}
		for (int j = 1; j <= __lg(n); j++) {
			for (int i = 1; i + (1LL << j) - 1 <= n; i++) {
				ST[j][i] = max(ST[j - 1][i], ST[j - 1][i + (1LL << (j - 1))]);
			}
		}
	}
	int query(int l, int r) {
		int len = __lg(r - l + 1);
		return max(ST[len][l], ST[len][r - (1LL << len) + 1]);
	}
};