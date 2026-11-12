/*
依赖 maxFlow_minCost_Ext.cpp。
用于修改边费用后，在总流量不变的条件下求最小费用。
每条边的费用为流量乘以单位费用。
调用前须满足容量限制和非源汇点的流量守恒。

int delta = cancel(G);
调整各边流量，返回总费用的变化量 delta，delta <= 0。
调整前后的费用都按新的单位费用计算，因此答案是调整前的总费用加 delta。
之后可继续用 G.aug 增广。
零流量时也可调用，以处理初始网络中的负环。

使用消负环算法。若消去 k 个负环，时间复杂度为 O(knm)。
整数费用、有限容量下会终止，但 k 可能很大。

示例：保持总流量为 2，修改一条边的单位费用。
Dinic G(2);
int id = G.add(1, 2, 2, 5);
G.add(1, 2, 2, 3);
auto [flow, cost] = G.dinic(1, 2, 2); // 2, 6
G.set(id, 2, 0, 1);
cost += cancel(G); // 费用变为 2，流量仍为 2。
*/
int cancel(Dinic &G) {
	int ans = 0;
	while (true) {
		G.h.assign(G.n + 1, 0);
		vector<int> pre(G.n + 1, -1);
		int x = -1;
		for (int k = 0; k <= G.n; k++) {
			x = -1;
			for (int i = 0; i < G.e.size(); i++) {
				auto [v, cap, cost] = G.e[i];
				int u = G.e[i ^ 1].x;
				if (cap > 0 && G.h[v] > G.h[u] + cost) {
					G.h[v] = G.h[u] + cost;
					pre[v] = i;
					x = v;
				}
			}
			if (x == -1) {
				return ans;
			}
		}
		for (int i = 0; i <= G.n; i++) {
			x = G.e[pre[x] ^ 1].x;
		}
		int f = inf, v = x;
		do {
			f = min(f, G.e[pre[v]].cap);
			v = G.e[pre[v] ^ 1].x;
		} while (v != x);
		do {
			int id = pre[v];
			ans += f * G.e[id].cost;
			G.e[id].cap -= f;
			G.e[id ^ 1].cap += f;
			v = G.e[id ^ 1].x;
		} while (v != x);
	}
}
