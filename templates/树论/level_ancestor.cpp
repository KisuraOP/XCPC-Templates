/*
时间复杂度 O(n log n) - O(1)

level_ancestor G(adj, rt);
adj 为邻接表，rt 为根节点编号。

int goal = G.query(x, k);
返回 x 的树上 k 级祖先。
*/

struct level_ancestor {
	int n;
	vector<int> dep, d, top, son;
	vector<vector<int>> adj, f, U, V;
	level_ancestor(vector<vector<int>> &Adj, int rt) {
		n = Adj.size() - 1;
		adj = Adj;
		init(rt);
	} 
	void init(int rt) {
		dep.resize(n + 1);
		d.resize(n + 1);
		top.resize(n + 1);
		son.resize(n + 1);
		U.resize(n + 1);
		V.resize(n + 1);
		f.resize(n + 1, vector<int>(23));
		dfs1(rt, 0);
		dfs2(rt, rt);
	}
	void dfs1(int x, int fa) {
		dep[x] = d[x] = d[f[x][0]] + 1;
		for (auto y : adj[x]) {
			if (y == fa) {
				continue;
			}
			f[y][0] = x;
			for (int i = 0; f[y][i]; i++) {
				f[y][i + 1] = f[f[y][i]][i];
			}
			dfs1(y, x);
			if (dep[y] > dep[x]) {
				dep[x] = dep[y];
				son[x] = y;
			}
		}
	}
	void dfs2(int x, int p) {
		top[x] = p;
		if (x == p) {
			for (int i = 0, o = x; i <= dep[x] - d[x]; i++) {
				U[x].push_back(o);
				o = f[o][0];
			}
			for (int i = 0, o = x; i <= dep[x] - d[x]; i++) {
				V[x].push_back(o);
				o = son[o];
			}
		}
		if (son[x]) {
			dfs2(son[x], p);
		}
		for (auto y : adj[x]) {
			if (y != son[x] && y != f[x][0]) {
				dfs2(y, y);
			}
		}
	}
	int query(int x, int k) {
		if (!k) {
			return x;
		}
		x = f[x][__lg(k)];
		k -= 1 << __lg(k);
		k -= d[x] - d[top[x]];
		x = top[x];
		if (k >= 0) {
			return U[x][k];
		} else {
			return V[x][-k];
		}
	}
};