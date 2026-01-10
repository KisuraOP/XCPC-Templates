/*
一般图：O(n^2 m)
二分图：O(m\sqrt n)

Dinic G(n);
n 为顶点数

G.add(u, v, cap);
连一条 u -> v 容量为 cap 的有向边。

int flow = G.dinic(S, T);
求解从源点 S 流向汇点 T 的最大流。

输出最小割方案：

vector<int> vis(n + 1);
auto dfs = [&] (auto self, int x) -> void {
	vis[x] = 1;
	for (auto i : G.adj[x]) {
		auto [y, cap] = G.e[i];
		if (!vis[y] && cap > 0) {
			self(self, y);
		}
	}
};
dfs(dfs, 源点编号);
for (int x = 1; x <= n; x++) {
	for (auto i : G.adj[x]) {
		auto [y, _] = G.e[i];
		if (vis[x] != vis[y]) {
			// 边 (x, y) 在方案中
		}
	}
}
*/

struct Dinic {
	struct Edge {
		int x, cap;
		Edge(int x, int cap) : x(x), cap(cap) {} 
	};
	int n;
	vector<Edge> e;
	vector<vector<int>> adj;
	vector<int> dep, cur;
	Dinic(int size) {
		this->n = size;
		adj.resize(n + 1);
	}
	void add(int x, int y, int cap) {
		adj[x].push_back(e.size());
		e.push_back({y, cap});
		adj[y].push_back(e.size());
		e.push_back({x, 0});
	}
	int bfs(int S, int T) {
		dep.assign(n + 1, -1);
		queue<int> q;
		q.push(S);
		dep[S] = 0;
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			for (auto i : adj[x]) {
				auto [y, cap] = e[i];
				if (cap > 0 && dep[y] == -1) {
					dep[y] = dep[x] + 1;
					if (y == T) {
						return true;
					}
					q.push(y);
				}
			}
		}
		return false;
	}
	int dfs(int x, int T, int limit) {
		if (x == T) {
			return limit;
		}
		int r = limit;
		for (int &i = cur[x]; i < adj[x].size(); i++) {
			const int j = adj[x][i];
			auto [y, cap] = e[j];
			if (cap > 0 && dep[y] == dep[x] + 1) {
				int t = dfs(y, T, min(r, cap));
				e[j].cap -= t;
				e[j ^ 1].cap += t;
				r -= t;
				if (r == 0) {
					return limit;
				}
			}
		}
		return limit - r;
	}
	int dinic(int S, int T) {
		int flow = 0;
		while (bfs(S, T)) {
			cur.assign(n + 1, 0);
			flow += dfs(S, T, inf); 
		} 
		return flow;
	}
};
