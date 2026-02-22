/*
时间复杂度 O(n log n) - O(1)

RMQ_LCA G(adj, rt);
adj 为邻接表。（默认带边权，若无边权可简单修改）
rt 为根, 可以不指定, 默认为 1。

以下操作时间复杂度均为 O(1)。

int lca = G.LCA(x, y);
返回 x 和 y 的 LCA。

int dis = G.dist(x, y);
返回 x 和 y 的树上距离（带权）。
*/

struct rmqLCA {
	int n;
	vector<int> dfn, dis;
	vector<array<int, 2>> st[21];
	rmqLCA(vector<vector<array<int, 2>>> &adj, int rt = 1) : n(adj.size() - 1), dfn(n + 1), dis(n + 1) {
		auto dfs = [&](auto self, int x, int f, int d, int w) -> void {
			dfn[x] = st[0].size();
			dis[x] = w;
			st[0].push_back({d, x});
			for (auto [y, wt] : adj[x]) {
				if (y != f) {
					self(self, y, x, d + 1, w + wt);
					st[0].push_back({d, x});
				}
			}
		};
		dfs(dfs, rt, 0, 0, 0);
		int sz = st[0].size();
		for (int i = 1; (1 << i) <= sz; i++) {
			st[i].resize(sz - (1 << i) + 1);
			for (int j = 0; j + (1 << i) <= sz; j++) {
				st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	int LCA(int x, int y) {
		int l = dfn[x], r = dfn[y];
		if (l > r) {
			swap(l, r);
		}
		int k = __lg(r - l + 1);
		return min(st[k][l], st[k][r - (1 << k) + 1])[1];
	}
	int dist(int x, int y) {
		return dis[x] + dis[y] - 2 * dis[LCA(x, y)];
	}
};