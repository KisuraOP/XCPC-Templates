/*
HLD h(adj, rt);

h.LCA(x, y) 返回最近公共祖先。
h.jump(x, k) 返回 x 的 k 级祖先，若不存在则返回 0。

h.path(x, y, f) 将路径上的点分成若干闭区间，逐段调用 f(l, r)。
各段不保证按从 x 到 y 的顺序调用。
需要按路径顺序处理时，使用 HLD_Ext.cpp 中的 walk。
h.path(x, y, f, true) 用于边权，边权存到较深端点。

dfn[x] 是 x 的 DFS 序，rev[i] 是第 i 个访问的点。
x 的子树对应 [dfn[x], dfn[x] + sz[x] - 1]。

预处理 O(n)，LCA、jump 和路径分段 O(log n)，不含回调开销。
*/
struct HLD {
	int n, tim;
	vector<vector<int>> adj;
	vector<int> fa, dep, sz, son;
	vector<int> top, dfn, rev;
	HLD(vector<vector<int>> &Adj, int rt) : n(Adj.size() - 1), 
	adj(Adj), fa(n + 1), dep(n + 1), sz(n + 1), son(n + 1), 
	top(n + 1), dfn(n + 1), rev(n + 1), tim(0) {
		dfs1(rt, 0);
		dfs2(rt, rt);
	}
	void dfs1(int x, int f) {
		dep[x] = dep[f] + 1;
		fa[x] = f;
		sz[x] = 1;
		int mx = 0;
		for (auto y : adj[x]) {
			if (y == f) {
				continue;
			}
			dfs1(y, x);
			sz[x] += sz[y];
			if (sz[y] > mx) {
				mx = sz[y];
				son[x] = y;
			}
		}
	}	
	void dfs2(int x, int t) {
		top[x] = t;
		dfn[x] = ++tim;
		rev[tim] = x;
		if (son[x] != 0) {
			dfs2(son[x], t);
		}	
		for (auto y : adj[x]) {
			if (y == fa[x] || y == son[x]) {
				continue;
			}
			dfs2(y, y);
		}
	}	
	int LCA(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) {
				swap(x, y);
			}
			x = fa[top[x]];
		} 
		return (dep[x] < dep[y] ? x : y);
	}
	int jump(int x, int k) {
		if (k >= dep[x]) {
			return 0;
		}
		int d = dep[x] - k;
		while (dep[top[x]] > d) {
			x = fa[top[x]];
		}
		return rev[dfn[x] - dep[x] + d];
	}
	template<class F>
	void path(int x, int y, F &&f, bool edge = false) {
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) {
				swap(x, y);
			}
			f(dfn[top[x]], dfn[x]);
			x = fa[top[x]];
		}
		if (dep[x] > dep[y]) {
			swap(x, y);
		}
		if (dfn[x] + edge <= dfn[y]) {
			f(dfn[x] + edge, dfn[y]);
		}
	}
};
