/*
容量为非负整数。O(nm log U)，U 为最大边容量。

Dinic G(n);

G.add(u, v, cap);
连一条 u -> v 容量为 cap 的有向边。

int flow = G.dinic(S, T);
返回本次增加的流量。同一对源汇可以继续增广。

最小割方案同 maxFlow.cpp。
*/

struct Dinic {
	struct Edge {
		int x, cap;
		Edge(int x, int cap) : x(x), cap(cap) {}
	};
	int n, lim;
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
				if (cap >= lim && dep[y] == -1) {
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
		for (int &i = cur[x]; i < adj[x].size(); i++) {
			const int j = adj[x][i];
			auto [y, cap] = e[j];
			if (cap >= lim && dep[y] == dep[x] + 1) {
				int t = dfs(y, T, min(limit, cap));
				if (t) {
					e[j].cap -= t;
					e[j ^ 1].cap += t;
					return t;
				}
			}
		}
		return 0;
	}
	int dinic(int S, int T) {
		int flow = 0, mx = 0;
		for (auto [y, cap] : e) {
			mx = max(mx, cap);
		}
		for (lim = 1; lim <= mx / 2; lim *= 2);
		for (; lim; lim /= 2) {
			while (bfs(S, T)) {
				cur.assign(n + 1, 0);
				while (int t = dfs(S, T, inf)) {
					flow += t;
				}
			}
		}
		return flow;
	}
};
