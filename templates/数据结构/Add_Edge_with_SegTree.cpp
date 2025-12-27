/* 
单次连出的边数为 O(log n)。

SegEdge seg(n);
初始化。

seg.PtoP(x, y);
连一条点 x 向点 y 的单向边。

seg.PtoS(x, l, r);
连一条点 x 向线段 [l, r] 的单向边。

seg.StoP(l, r, x);
连一条线段 [l, r] 向点 x 的单向边。

线段向线段连边：需要在初始化时预留额外空间，每次建一个虚点，线段向虚点连边再连向另一条线段即可。
*/

struct SegEdge {
	int n, K, all;
	vector<vector<array<int, 2>>> adj;
	vector<int> id;
	SegEdge() {}
	SegEdge(int n) {
		this->n = n;
		K = 4 * n;
		all = 8 * n;
		adj.resize(all + 1);
		id.resize(n + 1);
		build(1, 1, n);
		init(n);
	}
	void init(int n) {
		for (int i = 1; i <= n; i++) {
			adj[id[i]].push_back({id[i] + K, 0});
			adj[id[i] + K].push_back({id[i], 0});
		}
	}
	void build(int p, int l, int r) {
		if (l == r) return id[l] = p, void();
		adj[p].push_back({p << 1, 0});
		adj[p].push_back({p << 1 | 1, 0});
		adj[(p << 1) + K].push_back({p + K, 0});
		adj[(p << 1 | 1) + K].push_back({p + K, 0});
		int mid = l + r >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
	}
	void addEdge(int p, int l, int r, int lx, int rx, int x, int w, int opt) {
		if (lx <= l && r <= rx) {
			if (opt == 1) adj[x + K].push_back({p, w});
			else adj[p + K].push_back({x, w});
			return ;
		}
		int mid = l + r >> 1;
		if (lx <= mid) addEdge(p << 1, l, mid, lx, rx, x, w, opt);
		if (rx > mid) addEdge(p << 1 | 1, mid + 1, r, lx, rx, x, w, opt);
	}
	void PtoP(int x, int y, int w) {
		adj[id[x] + K].push_back({id[y], w});
	}
	void PtoS(int x, int l, int r, int w) {
		addEdge(1, 1, n, l, r, id[x], w, 1);
	}
	void StoP(int l, int r, int x, int w) {
		addEdge(1, 1, n, l, r, id[x], w, 2);
	}
	void StoS(int l1, int r1, int l2, int r2, int w) {
		++all;
		adj.resize(all + 1);
		StoP(l1, r1, all, 0);
		PtoS(all, l2, r2, w);
	}
};