/*
PseudoTree g(n);
g.addEdge(x, y, w);
g.work();
每个连通块恰有一个环，允许自环、重边。
有向查询则 addEdge 视为 x -> y。
加完边后调用 work，时间复杂度 O(n)。

cir[c] 按环序保存第 c 个环，ce[c][i] 是从 cir[c][i] 到下一点的边号。
e[j] 保存第 j 条边的两个端点和边权。

去掉所有环边后得到森林，每棵树以其中唯一的环上顶点为根。
rt[x] 是 x 所在树的根，id[x] 是连通块编号。
pos[x] 是 x 在环中的位置；不在环上时为 0。
fa[x]、pe[x] 是树中的父亲及父边，根的这两项均为 0。
dep[x]、dis[x] 是 x 到 rt[x] 的边数及距离。
ord 按从叶到根的顺序保存不在环上的点，可直接用于树形 DP。
*/
struct PseudoTree {
	int n;
	vector<array<int, 3>> e{{}};
	vector<vector<array<int, 2>>> adj;
	vector<vector<int>> cir, ce;
	vector<int> rt, id, pos, fa, pe, dep, dis, ord;
	PseudoTree(int n) : n(n), adj(n + 1), rt(n + 1), id(n + 1), pos(n + 1), fa(n + 1), pe(n + 1), dep(n + 1), dis(n + 1) {}
	void addEdge(int x, int y, int w = 1) {
		int j = e.size();
		e.push_back({x, y, w});
		adj[x].push_back({y, j});
		adj[y].push_back({x, j});
	}
	void work() {
		vector<int> deg(n + 1);
		ord.clear();
		cir.assign(1, {});
		ce.assign(1, {});
		for (int x = 1; x <= n; x++) {
			rt[x] = id[x] = pos[x] = fa[x] = pe[x] = dep[x] = dis[x] = 0;
			deg[x] = adj[x].size();
			if (deg[x] == 1) {
				ord.push_back(x);
			}
		}
		for (int i = 0; i < ord.size(); i++) {
			int x = ord[i];
			deg[x] = 0;
			for (auto [y, j] : adj[x]) {
				if (deg[y]) {
					fa[x] = y;
					pe[x] = j;
					if (--deg[y] == 1) {
						ord.push_back(y);
					}
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			if (!deg[i] || rt[i]) {
				continue;
			}
			cir.push_back({0});
			ce.push_back({0});
			int x = i, pre = 0;
			do {
				rt[x] = x;
				id[x] = cir.size() - 1;
				pos[x] = cir.back().size();
				cir.back().push_back(x);
				for (auto [y, j] : adj[x]) {
					if (deg[y] && j != pre) {
						ce.back().push_back(j);
						pre = j;
						x = y;
						break;
					}
				}
			} while (x != i);
		}
		for (int i = ord.size(); i--;) {
			int x = ord[i], y = fa[x];
			rt[x] = rt[y];
			id[x] = id[y];
			dep[x] = dep[y] + 1;
			dis[x] = dis[y] + e[pe[x]][2];
		}
	}
};
