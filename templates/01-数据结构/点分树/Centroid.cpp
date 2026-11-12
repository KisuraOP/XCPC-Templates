/*
Centroid t(n);

t.add(x, y, w);
连一条边权为 w 的无向边。

t.build(f);
执行点分治。
统计经过重心 x 的路径时，将统计代码写在 f(x, p) 中。
p 是上一层重心。

例：在每个重心处，收集各子树内的点到重心的距离。
t.build([&](int x, int p) {
    for (auto [y, w] : t.adj[x]) {
        if (t.del[y]) {
            continue;
        }
        vector<int> d;
        t.walk(y, x, w, [&](int z, int s) {
            d.push_back(s);
        });
        // 用 d 中的距离统计当前子树的贡献。
    }
});
walk 从邻居 y 出发遍历这棵子树，传给函数的 s 是 z 到重心 x 的距离。

时间复杂度 O(n log n)，不含 f 的开销。
*/
struct Centroid {
	vector<vector<array<int, 2>>> adj;
	vector<int> sz, del;
	Centroid(int n) : adj(n + 1), sz(n + 1), del(n + 1) {}
	void add(int x, int y, int w = 1) {
		adj[x].push_back({y, w});
		adj[y].push_back({x, w});
	}
	void dfs1(int x, int p) {
		sz[x] = 1;
		for (auto [y, w] : adj[x]) {
			if (y != p && !del[y]) {
				dfs1(y, x);
				sz[x] += sz[y];
			}
		}
	}
	int dfs2(int x, int p, int n) {
		for (auto [y, w] : adj[x]) {
			if (y != p && !del[y] && sz[y] * 2 > n) {
				return dfs2(y, x, n);
			}
		}
		return x;
	}
	int root(int x) {
		dfs1(x, 0);
		return dfs2(x, 0, sz[x]);
	}
	template<class F>
	void walk(int x, int p, int d, F &&f) {
		f(x, d);
		for (int i = adj[x].size() - 1; i >= 0; i--) {
			auto [y, w] = adj[x][i];
			if (y != p && !del[y]) {
				walk(y, x, d + w, f);
			}
		}
	}
	template<class F>
	void build(F &&f, int x = 1, int p = 0) {
		x = root(x);
		del[x] = 1;
		f(x, p);
		for (auto [y, w] : adj[x]) {
			if (!del[y]) {
				build(f, y, x);
			}
		}
	}
};
