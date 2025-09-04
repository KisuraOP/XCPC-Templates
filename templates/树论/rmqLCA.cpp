/*
时间复杂度 O(n log n) - O(1)

RMQ_LCA G(adj);
adj 为邻接表。（默认无边权，若有边权可简单修改）

G.work(rt);
rt 为根节点编号。

int lca = G.LCA(x, y);
O(1) 返回 x 和 y 的 LCA。

int dis = G.dist(x, y);
O(1) 返回 x 和 y 的树上距离。

int goal = G.jump(x, len);
O(logn) 返回 x 的 len 级祖先。
此处为倍增，可替换为 O(1) 树上 k 级祖先的模板，但很多时候都没必要。
*/

struct RMQ_LCA {
	int n, tim;
	vector<int> dfn, rdfn, lg, dep, twdep, sz;
	vector<vector<int>> adj, fa, A, B;
	RMQ_LCA(vector<vector<int>> &Adj) {
		this->n = Adj.size() - 1;
		adj = Adj;
		init();
	}
	void init() {
		dfn.resize(n + 1);
		rdfn.resize(2 * n + 1);
		lg.resize(2 * n + 1);
		dep.resize(n + 1);
		twdep.resize(2 * n + 1);
		sz.assign(n + 1, 1);
		tim = 0;
		for (int i = 2; i <= 2 * n; i++) {
			lg[i] = lg[i >> 1] + 1;
		}
	}
	void dfs(int x, int fath, int d) {
		dfn[x] = ++tim;
		rdfn[tim] = x;
		twdep[tim] = d;

		dep[x] = dep[fath] + 1;
		fa[x][0] = fath;
		for (int i = 1; i <= lg[dep[x]] + 1; i++) {
			fa[x][i] = fa[fa[x][i - 1]][i - 1];
		}

		for (auto y : adj[x]) {
			if (!dfn[y]) {
				dfs(y, x, d + 1);
				rdfn[++tim] = x;
				twdep[tim] = d;
				sz[x] += sz[y];
			}
		}
	}
	void work(int rt) {
		fa.resize(n + 1, vector<int>(21));
		dfs(rt, 0, 1);

		A.resize(21, vector<int>(tim + 1));
		B.resize(21, vector<int>(tim + 1));
		for (int i = 1; i <= tim; i++) {
			A[0][i] = twdep[i];
			B[0][i] = rdfn[i];
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
		return dep[x] + dep[y] - 2 * dep[LCA(x, y)];
	}
	int jump(int x, int len) {
		for (int i = 20; i >= 0; i--) {
			if (len >> i & 1) {
				x = fa[x][i];
			}
		}
		return x;
	}
};