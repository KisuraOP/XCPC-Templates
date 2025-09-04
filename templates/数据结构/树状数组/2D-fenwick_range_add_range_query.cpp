/*
Fenwick fen(n, m);
创建。

fen.add(x1, y1, x2, y2, v);
给左上角 (x1, y1) 右下角 (x2, y2) 围成的矩形 +v。

int res = fen.sum(x1, y1, x2, y2);
求左上角 (x1, y1) 右下角 (x2, y2) 围成的矩形内数的和。
*/

struct Fenwick {
	vector<vector<int>> f1, f2, f3, f4; 
	int n, m;
	Fenwick(int _n, int _m) : n(_n), m(_m) {
		f1.assign(_n + 1, vector<int>(_m + 1));
		f2.assign(_n + 1, vector<int>(_m + 1));
		f3.assign(_n + 1, vector<int>(_m + 1));
		f4.assign(_n + 1, vector<int>(_m + 1));
	} 
	void modify(int x, int y, int v) {
		for (int i = x; i <= n; i += i & -i) {
			for (int j = y; j <= m; j += j & -j) {
				f1[i][j] += v;
				f2[i][j] += v * x;
				f3[i][j] += v * y;
				f4[i][j] += v * x * y;
			}
		}
	}
	int get(int x, int y) {
		int res = 0;
		for (int i = x; i > 0; i -= i & -i) {
			for (int j = y; j > 0; j -= j & -j) {
				res += (x + 1) * (y + 1) * f1[i][j]
					- (y + 1) * f2[i][j]
					- (x + 1) * f3[i][j]
					+ f4[i][j];
			}
		}
		return res;
	}
	void add(int x1, int y1, int x2, int y2, int v) {
		modify(x1, y1, v);
		modify(x1, y2 + 1, -v);
		modify(x2 + 1, y1, -v);
		modify(x2 + 1, y2 + 1, v);
	}
	int sum(int x1, int y1, int x2, int y2) {
		return get(x2, y2) - get(x2, y1 - 1) - get(x1 - 1, y2) + get(x1 - 1, y1 - 1);
	}
};