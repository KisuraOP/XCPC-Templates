/*
时间复杂度 O(n log n) - O(1)

RMQ_LCA G(adj);
adj 为邻接表。（默认无边权，若有边权可简单修改）

G.work();

int lca = G.LCA(x, y);
O(1) 返回 x 和 y 的 LCA。

int dis = G.dist(x, y);
O(1) 返回 x 和 y 的树上距离（带权）。
*/

struct RMQ_LCA {
	int n, tim;
	vector<int> dfn, rev, lg, dep, tdep, a;
	vector<vector<array<int, 2>>> adj;
	vector<vector<int>> A, B;
	RMQ_LCA(vector<vector<array<int, 2>>> &Adj) : n(Adj.size() - 1), adj(Adj), tim(0), 
	dfn(n + 1), rev(2 * n + 1), lg(2 * n + 1), dep(n + 1), tdep(2 * n + 1), a(n + 1) {
		for (int i = 2; i <= 2 * n; i++) {
			lg[i] = lg[i >> 1] + 1;
		}
		work();
	}
	void dfs(int x, int f, int d, int w) {
		dfn[x] = ++tim;
		rev[tim] = x;
		tdep[tim] = d;

		dep[x] = dep[f] + 1;
		a[x] = a[f] + w;

		for (auto [y, w] : adj[x]) {
			if (!dfn[y]) {
				dfs(y, x, d + 1, w);
				rev[++tim] = x;
				tdep[tim] = d;
			}
		}
	}
	void work() {
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) {
				dfs(i, 0, 1, 1);
			}
		}
		A.resize(20, vector<int>(tim + 1));
		B.resize(20, vector<int>(tim + 1));
		for (int i = 1; i <= tim; i++) {
			A[0][i] = tdep[i];
			B[0][i] = rev[i];
		}
		for (int i = 1; i <= lg[tim]; i++) {
			for (int j = 1; j + (1LL << i) - 1 <= tim; j++) {
				if (A[i - 1][j] < A[i - 1][j + (1LL << i - 1)]) {
					A[i][j] = A[i - 1][j];
					B[i][j] = B[i - 1][j];
				} else {
					A[i][j] = A[i - 1][j + (1LL << i - 1)];
					B[i][j] = B[i - 1][j + (1LL << i - 1)];
				}
			}
		}
	}
	int LCA(int x, int y) {
		int l = min(dfn[x], dfn[y]);
		int r = max(dfn[x], dfn[y]);
		int k = lg[r - l + 1];
		if (A[k][l] < A[k][r + 1 - (1LL << k)]) {
			return B[k][l];
		} else {
			return B[k][r + 1 - (1LL << k)];
		}
	}
	int dist(int x, int y) {
		return a[x] + a[y] - 2 * a[LCA(x, y)];
	}
};