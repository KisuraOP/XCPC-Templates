/*
Centroid t(n);
1-index。

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
	vector<int> sz, fa, del;
	Centroid(int n) : adj(n + 1), sz(n + 1), fa(n + 1), del(n + 1) {}
	void add(int x, int y, int w = 1) {
		adj[x].push_back({y, w});
		adj[y].push_back({x, w});
	}
	int root(int x) {
		vector<int> v{x};
		fa[x] = 0;
		for (int i = 0; i < v.size(); i++) {
			int u = v[i];
			for (auto [y, w] : adj[u]) {
				if (y != fa[u] && !del[y]) {
					fa[y] = u;
					v.push_back(y);
				}
			}
		}
		int n = v.size(), rt = x;
		for (int i = n - 1; i >= 0; i--) {
			int u = v[i], mx = 0;
			sz[u] = 1;
			for (auto [y, w] : adj[u]) {
				if (y != fa[u] && !del[y]) {
					sz[u] += sz[y];
					mx = max(mx, sz[y]);
				}
			}
			if (max(mx, n - sz[u]) * 2 <= n) {
				rt = u;
			}
		}
		return rt;
	}
	template<class F>
	void walk(int x, int p, int d, F &&f) {
		vector<array<int, 3>> st{{x, p, d}};
		while (!st.empty()) {
			auto [x, p, d] = st.back();
			st.pop_back();
			f(x, d);
			for (auto [y, w] : adj[x]) {
				if (y != p && !del[y]) {
					st.push_back({y, x, d + w});
				}
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
