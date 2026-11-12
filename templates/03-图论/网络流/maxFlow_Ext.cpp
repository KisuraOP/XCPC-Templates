/*
Dinic，支持查询和修改边信息、清空流量，以及限制本次增加的流量。
一般图：O(n^2 m)
二分图：O(m\sqrt n)

Dinic G(n);

int id = G.add(u, v, cap);
添加容量为 cap 的有向边 u -> v，返回正向边编号。
反向边编号为 id ^ 1，两者的 cap 分别为剩余容量和流量。

auto [u, v, cap, flow] = G.get(id);
查询原边的起点、终点、容量和流量。

G.set(id, cap, flow);
将原边的容量和流量设为 cap、flow，同时更新反向边。
只改容量时，flow 传原流量。
修改流量后，须保证除源点、汇点外各点的流量守恒，才能继续增广。

G.reset();
清空所有流量，保留当前容量。O(m)。
清空后可以更换源点、汇点，再计算最大流。

int flow = G.dinic(S, T, lim);
从 S 向 T 至多增加 lim 单位流，返回本次增加的流量。
使用同一对源汇，可以反复调用以继续增广。
加边或增加容量后可以继续增广；减小容量时不能小于该边已有流量。

auto vis = G.cut(S);
vis[v] 表示残量网络中能否从 S 到达 v。O(n+m)。
求完最大流后，可达点与不可达点构成最小割。
若仅因增加的流量达到 lim 而停止，这个划分不一定是最小割。

输出最小割方案：

G.dinic(S, T);
auto vis = G.cut(S);
for (int x = 0; x <= n; x++) {
	for (auto i : G.adj[x]) {
		auto [y, _] = G.e[i];
		if (vis[x] && !vis[y] && !(i & 1)) {
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
	int add(int x, int y, int cap) {
		adj[x].push_back(e.size());
		e.push_back({y, cap});
		adj[y].push_back(e.size());
		e.push_back({x, 0});
		return e.size() - 2;
	}
	array<int, 4> get(int id) {
		return {e[id ^ 1].x, e[id].x, e[id].cap + e[id ^ 1].cap, e[id ^ 1].cap};
	}
	void set(int id, int cap, int flow) {
		e[id].cap = cap - flow;
		e[id ^ 1].cap = flow;
	}
	void reset() {
		for (int i = 0; i < e.size(); i += 2) {
			e[i].cap += e[i ^ 1].cap;
			e[i ^ 1].cap = 0;
		}
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
	int dinic(int S, int T, int lim = inf) {
		int flow = 0;
		while (flow < lim && bfs(S, T)) {
			cur.assign(n + 1, 0);
			flow += dfs(S, T, lim - flow);
		} 
		return flow;
	}
	vector<int> cut(int S) {
		bfs(S, -1);
		auto vis = dep;
		for (auto &x : vis) {
			x = x != -1;
		}
		return vis;
	}
};
