#define _node vector<vector<array<int, 2>>>
struct Node {
	int n;
	_node adj;
	vector<vector<int>> fa, dis;
	vector<int> dep;
	Node(int size) {
		this->n = size;
		adj.resize(n + 1, {});
		fa.resize(n + 1, vector<int>(25));
		dis.resize(n + 1, vector<int>(25));
		dep.resize(n + 1);
	}
	void add(int x, int y, int w) {
		adj[x].push_back({y, w});
		adj[y].push_back({x, w});
	}
	void dfs(int x, int fath, int w) {
		fa[x][0] = fath;
		dis[x][0] = w;
		dep[x] = dep[fath] + 1;
		for (int i = 1; i <= __lg(dep[x]) + 1; i++) {
			fa[x][i] = fa[fa[x][i - 1]][i - 1];
			dis[x][i] = max(dis[x][i - 1], dis[fa[x][i - 1]][i - 1]);
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
		if (dep[x] < dep[y]) {
			swap(x, y);
		}
		while (dep[x] > dep[y]) {
			x = fa[x][__lg(dep[x] - dep[y])];
		}
		if (x == y) {
			return x;
		} 
		for (int i = __lg(dep[x]); i >= 0; i--) {
			if (fa[x][i] != fa[y][i]) {
				x = fa[x][i];
				y = fa[y][i];
			}
		}
		return fa[x][0];
	}
	int dist(int x, int y) {
		int res = 0;
		if (dep[x] < dep[y]) {
			swap(x, y);
		}
		while (dep[x] > dep[y]) {
			res = max(res, dis[x][__lg(dep[x] - dep[y])]);
			x = fa[x][__lg(dep[x] - dep[y])];
		}
		return res;
	}
	int getmx(int x, int y) {
		int lca = LCA(x, y);
		return max(dist(x, lca), dist(y, lca));
	}
};