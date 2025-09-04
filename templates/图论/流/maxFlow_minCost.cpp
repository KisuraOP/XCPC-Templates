/*
原始对偶算法。
时间复杂度：O(fm\log n)。

Dinic G(n);
n 为顶点数。

G.add(x, y, cap, cost);
连一条 x -> y 容量为 cap，费用为 cost 的边。

auto [flow, cost] = G.dinic(S, T);
以 S 为源点，T 为汇点跑最小费用最大流。返回一个 [最大流量，最小费用] 的二元组。
*/

struct Dinic {
	struct Edge {
		int x, cap, cost;
		Edge(int x, int cap, int cost) : x(x), cap(cap), cost(cost) {}
	};
	int n;
	vector<Edge> e;
	vector<vector<int>> adj;
	vector<int> dis, pre;
	vector<int> h;
	Dinic(int size) {
		this->n = size;
		adj.resize(n + 1);
	}
	void add(int x, int y, int w, int f) {
		adj[x].push_back(e.size());
		e.push_back({y, w, f});
		adj[y].push_back(e.size());
		e.push_back({x, 0, -f});
	}
	bool dijkstra(int S, int T) {
		dis.assign(n + 1, inf);
		pre.assign(n + 1, -1);
		#define Pair pair<int, int>
		priority_queue<Pair, vector<Pair>, greater<Pair>> q;
		dis[S] = 0;
		q.push({0, S});
		while (!q.empty()) {
			auto [d, x] = q.top();
			q.pop();
			if (dis[x] != d) {
				continue;
			}
			for (auto i : adj[x]) {
				auto [y, cap, cost] = e[i];
				if (cap > 0 && dis[y] > d + h[x] - h[y] + cost) {
					dis[y] = d + h[x] - h[y] + cost;
					pre[y] = i;
					q.push({dis[y], y});
				}
			}
		}
		return (dis[T] != inf);
	}
	array<int, 2> dinic(int S, int T) {
		int flow = 0, cost = 0;
		h.assign(n + 1, 0);
		while (dijkstra(S, T)) {
			for (int i = 1; i <= n; i++) {
				h[i] += dis[i];
			}
			int res = inf;
			for (int i = T; i != S; i = e[pre[i] ^ 1].x) {
				res = min(res, e[pre[i]].cap);
			}
			for (int i = T; i != S; i = e[pre[i] ^ 1].x) {
				e[pre[i]].cap -= res;
				e[pre[i] ^ 1].cap += res;
			}
			flow += res;
			cost += res * h[T];

		}
		return {flow, cost};
	}
};