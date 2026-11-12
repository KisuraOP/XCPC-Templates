/*
LP lp(a, b, c);
vector<double> x;
double ans = lp.solve(x);

最大化 c^T x，约束为 ax <= b、x >= 0。
若无解则返回 -inf，若目标无界则返回 inf；否则返回最优值，x 为一组最优解。
*/

constexpr double eps = 1e-9;
struct LP {
	int m, n;
	vector<int> bas, non;
	vector<vector<double>> t;
	LP(const vector<vector<double>> &a, const vector<double> &b, const vector<double> &c) :
		m(b.size() - 1), n(c.size() - 1), bas(m + 1), non(n + 2), t(m + 3, vector<double>(n + 3)) {
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				t[i][j] = a[i][j];
			}
			bas[i] = n + i;
			t[i][n + 1] = -1;
			t[i][n + 2] = b[i];
		}
		for (int j = 1; j <= n; j++) {
			non[j] = j;
			t[m + 1][j] = -c[j];
		}
		t[m + 2][n + 1] = 1;
	}
	void pivot(int r, int s) {
		double k = 1 / t[r][s];
		for (int i = 1; i <= m + 2; i++) {
			if (i != r) {
				for (int j = 1; j <= n + 2; j++) {
					if (j != s) {
						t[i][j] -= t[r][j] * t[i][s] * k;
					}
				}
			}
		}
		for (int j = 1; j <= n + 2; j++) {
			if (j != s) {
				t[r][j] *= k;
			}
		}
		for (int i = 1; i <= m + 2; i++) {
			if (i != r) {
				t[i][s] *= -k;
			}
		}
		t[r][s] = k;
		swap(bas[r], non[s]);
	}
	bool run(int p) {
		while (true) {
			int r = 0, s = 0;
			for (int j = 1; j <= n + 1; j++) {
				if (non[j] && t[m + p][j] < -eps && (!s || non[j] < non[s])) {
					s = j;
				}
			}
			if (!s) {
				return true;
			}
			double v = inf;
			for (int i = 1; i <= m; i++) {
				if (t[i][s] > eps) {
					double w = t[i][n + 2] / t[i][s];
					if (!r || w < v || (w == v && bas[i] < bas[r])) {
						r = i;
						v = w;
					}
				}
			}
			if (!r) {
				return false;
			}
			pivot(r, s);
		}
	}
	double solve(vector<double> &x) {
		int r = 0;
		for (int i = 1; i <= m; i++) {
			if (!r || t[i][n + 2] < t[r][n + 2]) {
				r = i;
			}
		}
		if (r && t[r][n + 2] < -eps) {
			pivot(r, n + 1);
			if (!run(2) || t[m + 2][n + 2] < -eps) {
				return -inf;
			}
			for (int i = 1; i <= m; i++) {
				if (!bas[i]) {
					int s = 0;
					for (int j = 1; j <= n + 1; j++) {
						if (non[j] && abs(t[i][j]) > eps && (!s || non[j] < non[s])) {
							s = j;
						}
					}
					if (s) {
						pivot(i, s);
					}
				}
			}
		}
		bool ok = run(1);
		x.assign(n + 1, 0);
		for (int i = 1; i <= m; i++) {
			if (bas[i] && bas[i] <= n) {
				x[bas[i]] = t[i][n + 2];
			}
		}
		return ok ? t[m + 1][n + 2] : inf;
	}
};
