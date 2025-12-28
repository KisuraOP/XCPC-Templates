// 判断 GF(3) 下一个向量是否能被一个向量组线性表出
struct Basis {
	int n;
	vector<vector<int>> p;
	Basis(int _n) : n(_n), p(n) {}
	void insert(vector<int> v) {
		for (int i = n - 1; i >= 0; i--) {
			if (v[i] == 0) {
				continue;
			}
			if (p[i].empty()) {
				p[i] = v;
				return ;
			}
			int fac = v[i] * p[i][i] % 3;
			for (int j = 0; j < n; j++) {
				v[j] = (v[j] - fac * p[i][j] % 3 + 3) % 3;
			}
		}
	}
	bool query(vector<int> v) {
		for (int i = n - 1; i >= 0; i--) {
			if (v[i] == 0) {
				continue;
			}
			if (p[i].empty()) {
				return false;
			}
			int fac = v[i] * p[i][i] % 3;
			for (int j = 0; j < n; j++) {
				v[j] = (v[j] - fac * p[i][j] % 3 + 3) % 3;
			}
		}
		return true;
	}
};