/*
原始对偶算法。
初始化 O(n+nm)，增广 O(f(n+m\log m))。
允许负费用边，增广前要求残量网络中没有负环。

Dinic G(n);

int id = G.add(x, y, cap, cost);
添加容量为 cap、单位费用为 cost 的有向边 x -> y，返回正向边编号。
反向边编号为 id ^ 1，两者的 cap 分别为剩余容量和流量。

auto [u, v, cap, flow, cost] = G.get(id);
查询原边的起点、终点、容量、流量和单位费用。

G.set(id, cap, flow, cost);
将原边的容量、流量和单位费用设为 cap、flow、cost，同时更新反向边。
要求 0 <= flow <= cap。只改容量或费用时，flow 传原流量。
set 不维护流量守恒。修改流量时须成组调整相关边，
并在继续求解前保证非源汇点的流入量等于流出量。

G.reset();
清空所有流量，保留当前容量和单位费用。O(m)。
清空后可换源汇重新求解。

auto [flow, cost] = G.dinic(S, T, lim);
从 S 向 T 至多增加 lim 单位流，返回本次增加的流量和费用。

G.init();
计算用于 Dijkstra 的势函数 G.h，不改变各边流量。
若所有有剩余容量的边费用非负，可直接 G.h.assign(n + 1, 0)。
也可自行设置 h，使每条有剩余容量的边 u -> v 满足 cost+h[u]-h[v] >= 0。

auto [flow, cost] = G.aug(S, T, lim);
沿一条最短路至多增广 lim，返回本次流量和费用；没有增广路时返回 {0, 0}。
先初始化 h，再使用同一对源汇反复调用。成功后可通过 G.pre 回溯本次路径。
若在两次调用之间修改边费用，须保证 h 仍满足上述条件，或重新初始化。

init 只计算势函数，不会调整已有流量。
修改费用后若出现负环，先用 maxFlow_minCost_Cancel.cpp 中的 cancel(G) 处理。

逐次增广并遍历增广路：
G.init();
while (true) {
	auto [flow, cost] = G.aug(S, T, 1);
	if (!flow) {
		break;
	}
	for (int x = T; x != S;) {
		int id = G.pre[x];
		x = G.e[id ^ 1].x;
	}
}
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
	int add(int x, int y, int w, int f) {
		adj[x].push_back(e.size());
		e.push_back({y, w, f});
		adj[y].push_back(e.size());
		e.push_back({x, 0, -f});
		return e.size() - 2;
	}
	array<int, 5> get(int id) {
		return {e[id ^ 1].x, e[id].x, e[id].cap + e[id ^ 1].cap, e[id ^ 1].cap, e[id].cost};
	}
	void set(int id, int cap, int flow, int cost) {
		e[id].cap = cap - flow;
		e[id ^ 1].cap = flow;
		e[id].cost = cost;
		e[id ^ 1].cost = -cost;
	}
	void reset() {
		for (int i = 0; i < e.size(); i += 2) {
			e[i].cap += e[i ^ 1].cap;
			e[i ^ 1].cap = 0;
		}
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
	void init() {
		h.assign(n + 1, 0);
		for (int k = 0; k < n; k++) {
			bool ok = false;
			for (int i = 0; i < e.size(); i++) {
				auto [y, cap, w] = e[i];
				int x = e[i ^ 1].x;
				if (cap > 0 && h[y] > h[x] + w) {
					h[y] = h[x] + w;
					ok = true;
				}
			}
			if (!ok) {
				break;
			}
		}
	}
	array<int, 2> aug(int S, int T, int lim = inf) {
		if (!lim || !dijkstra(S, T)) {
			return {0, 0};
		}
		for (int i = 0; i <= n; i++) {
			if (dis[i] != inf) {
				h[i] += dis[i];
			}
		}
		int res = lim;
		for (int i = T; i != S; i = e[pre[i] ^ 1].x) {
			res = min(res, e[pre[i]].cap);
		}
		for (int i = T; i != S; i = e[pre[i] ^ 1].x) {
			e[pre[i]].cap -= res;
			e[pre[i] ^ 1].cap += res;
		}
		return {res, res * (h[T] - h[S])};
	}
	array<int, 2> dinic(int S, int T, int lim = inf) {
		init();
		int flow = 0, cost = 0;
		while (flow < lim) {
			auto [f, c] = aug(S, T, lim - flow);
			if (!f) {
				break;
			}
			flow += f;
			cost += c;
		}
		return {flow, cost};
	}
};