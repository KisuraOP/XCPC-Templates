/*
时间复杂度 O(n log n)

VirtualTree G(n);
n 为顶点数。

G.add(x, y, w);
连一条 x -> y 边权为 w 的双向边。

G.init(rt);
选取 rt 为虚树的根，初始化。

_node adj = G.getTree(a);
以 a 数组（0-index）中的点为关键节点建立虚树，返回虚树的邻接表。
虚树上节点间的距离可通过 dist 函数定义，默认为原树中两点间边的数量。
G.id[x] 代表原树中的节点 x 在虚树中的编号。
*/

#define _node vector<vector<array<int, 2>>>
struct VirtualTree {
	int n;
	_node adj;
	vector<vector<int>> fa;
	vector<int> dfn, depth, id;
	int tim = 0, tot = 0;
	VirtualTree(int size) {
		this->n = size;
		adj.resize(n + 1, {});
		fa.resize(n + 1, vector<int>(25));
		dfn.resize(n + 1);
		depth.resize(n + 1);
		id.resize(n + 1);
	}
	void add(int x, int y, int w) {
		adj[x].push_back({y, w});
		adj[y].push_back({x, w});
	}
	void dfs(int x, int fath, int w) {
		dfn[x] = ++tim;
		fa[x][0] = fath;
		depth[x] = depth[fath] + 1;
		for (int i = 1; i <= __lg(depth[x]) + 1; i++) {
			fa[x][i] = fa[fa[x][i - 1]][i - 1];
		}
		for (auto [y, z] : adj[x]) {
			if (y != fath) {
				dfs(y, x, z);
			}
		}
	}
	void init(int rt) {
		dfs(rt, 0, 0);
	}
	int LCA(int x, int y) {
		if (depth[x] < depth[y]) {
			swap(x, y);
		}
		while (depth[x] > depth[y]) {
			x = fa[x][__lg(depth[x] - depth[y])];
		}
		if (x == y) {
			return x;
		} 
		for (int i = __lg(depth[x]); i >= 0; i--) {
			if (fa[x][i] != fa[y][i]) {
				x = fa[x][i];
				y = fa[y][i];
			}
		}
		return fa[x][0];
	}
	int dist(int x, int y) {
		return depth[x] + depth[y] - 2 * depth[LCA(x, y)];
	}
	vector<int> b;
	void Add(_node &Adj, int x, int y) {
		int w = dist(x, y);
		// cout << "Add (" << x << " -> " << y << ", " << w << ")\n"; 
		if (id[x] == 0) {
			id[x] = ++tot;
			b.push_back(x);
		}
		if (id[y] == 0) {
			id[y] = ++tot;
			b.push_back(y);
		}
		Adj[id[x]].push_back({id[y], w});
	}
	void Del() {
		while (!b.empty()) {
			id[b.back()] = 0;
			b.pop_back();
		}
		tot = 0;
	}
	_node getTree(vector<int> &a) {
		Del();
		int sz = 2 * a.size() + 1;
		int top = 1;
		sort(a.begin(), a.end(), [&] (int i, int j) {
			return dfn[i] < dfn[j];
		});

		_node Adj(sz + 1);
		vector<int> stk(sz + 1);
		stk[top] = 1;
		for (auto x : a) {
			if (x == 1) {
				continue;
			}
			int lca = LCA(x, stk[top]);
			if (lca != stk[top]) {
				while (top > 1 && dfn[stk[top - 1]] > dfn[lca]) {
					Add(Adj, stk[top - 1], stk[top]);
					top--;
				}
				if (lca != stk[top - 1]) {
					Adj[id[lca]].clear();
					Add(Adj, lca, stk[top]);
					stk[top] = lca;
				} else {
					Add(Adj, lca, stk[top]);
					top--;
				}
			}
			Adj[id[x]].clear();
			stk[++top] = x;
		}
		while (top > 1) {
			Add(Adj, stk[top - 1], stk[top]);
			top--;
		}
		return Adj;
	}
};