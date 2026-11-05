/*
依赖 maxFlow_minCost_Ext.cpp。
处理边的单位费用随流量变化的最小费用流。
fee(id, f) 给出原边 id 的第 f 单位流的费用，f 从 1 开始。
对每条原边，fee(id, f) 须随 f 非递减。流量为 f 时，费用为前 f 项之和。

auto [flow, cost] = convex(G, S, T, fee);
沿最短路增广 1 单位，并更新路径上的边费用。
返回本次流量和费用；没有增广路时返回 {0, 0}。

建图时，将正向边费用设为 fee(id, 1)；容量为 0 的边费用可任取。
先初始化 G.h，再调用 convex。
函数只会查询第 1 单位到原边容量之间的费用。
convex 会在增广后更新费用，G.dinic 不会调用 fee。
调用 G.reset 后，须恢复各边的正向初始费用，再初始化 G.h。

示例：两条边通过第 1、2、3 单位流的费用分别为 {1, 2, 10} 和 {3, 3, 3}。
vector<vector<int>> a = {{1, 2, 10}, {3, 3, 3}};
auto fee = [&](int id, int f) {
	return a[id / 2][f - 1];
};
Dinic G(2);
G.add(1, 2, 3, a[0][0]);
G.add(1, 2, 3, a[1][0]);
G.init();
int ans = 0;
for (int i = 0; i < 3; i++) {
	auto [flow, cost] = convex(G, 1, 2, fee);
	ans += cost;
}
cout << ans; // 6
*/
template<class F>
array<int, 2> convex(Dinic &G, int S, int T, F fee) {
	auto ans = G.aug(S, T, 1);
	if (ans[0]) {
		for (int x = T; x != S;) {
			int id = G.pre[x], j = id / 2 * 2;
			int f = G.e[j ^ 1].cap;
			if (G.e[j].cap) {
				G.e[j].cost = fee(j, f + 1);
			}
			if (f) {
				G.e[j ^ 1].cost = -fee(j, f);
			}
			x = G.e[id ^ 1].x;
		}
	}
	return ans;
}
