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
	void path_add(LazySegmentTree<Info, Tag> &seg, 
				  int x, int y, const Tag &w) {
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) {
				swap(x, y);
			}
			seg.modify(dfn[top[x]], dfn[x], {w});
			x = fa[top[x]];
		}
		if (dep[x] > dep[y]) {
			swap(x, y);
		}
		seg.modify(dfn[x], dfn[y], {w});
	}
	Z path_query(LazySegmentTree<Info, Tag> &seg, 
				 int x, int y) {
		Z res = 0;
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) {
				swap(x, y);
			}
			res += seg.query(dfn[top[x]], dfn[x]).sum;
			x = fa[top[x]];
		}
		if (dep[x] > dep[y]) {
			swap(x, y);
		}
		res += seg.query(dfn[x], dfn[y]).sum;
		return res;
	}
};