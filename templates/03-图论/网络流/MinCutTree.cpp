/*
先在这里完整抄写 Dinic (maxFlow.cpp)
唯一修改如下。

void add(int x, int y, int cap) {
	adj[x].push_back(e.size());
	e.push_back({y, cap});
	adj[y].push_back(e.size());
	// 【唯一修改】 注意下面这一行
	e.push_back({x, cap});
}
*/

// Gusfield Algorithm
struct MinCutTree {
	struct Edge {
		int x, cap;
	};
	int n;
	vector<vector<Edge>> tr;
	vector<array<int, 3>> E;
	MinCutTree(int n) : n(n), tr(n + 1) {}
	// 添加一条无向边
	void add(int x, int y, int cap) {
		E.push_back({x, y, cap});
	}
	// O(n^3 m)
	void build() {
		vector<int> p(n + 1, 1);
		for (int i = 2; i <= n; i++) {
			Dinic G(n);
			for (auto [x, y, cap] : E) {
				G.add(x, y, cap);
			}
			int flow = G.dinic(i, p[i]);
			tr[i].push_back({p[i], flow});
			tr[p[i]].push_back({i, flow});
			for (int j = i + 1; j <= n; j++) {
				if (p[j] == p[i] && G.dep[j] != -1) {
					p[j] = i;
				}
			}
		}
	}
	// 返回最小割。 O(n)
	int min_cut(int u, int v) {
		int ans = inf;
		auto dfs = [&] (auto self, int x, int p) -> bool {
			if (x == v) {
				return true;
			}
			for (auto [y, cap] : tr[x]) {
				if (y != p && self(self, y, x)) {
					ans = min(ans, cap);
					return true;
				}
			}
			return false;
		};
		dfs(dfs, u, 0);
		return ans;
	}
	// 返回最小割方案, 一个 bool 数组, true 表示与 u 在同一侧。 O(n)
	vector<int> get_partition(int u, int v) {
		int min_w = inf;
		int cu = 0, cv = 0;
		auto dfs1 = [&] (auto self, int x, int p) -> bool {
			if (x == v) {
				return true;
			}
			for (auto [y, cap] : tr[x]) {
				if (y != p && self(self, y, x)) {
					if (cap < min_w) {
						min_w = cap;
						cu = x;
						cv = y;
					}
					return true;
				}
			}
			return false;
		};
		dfs1(dfs1, u, 0);
		vector<int> ans(n + 1);
		auto dfs2 = [&] (auto self, int x, int p) -> void {
			ans[x] = true;
			for (auto [y, cap] : tr[x]) {
				int is_cut = (x == cu && y == cv) || (x == cv && y == cu);
				if (y != p && !is_cut) {
					self(self, y, x);
				}
			}
		};
		dfs2(dfs2, u, 0);
		return ans;
	}
};