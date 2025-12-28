/*
一般图最大权匹配 O(n^3)

Weighted_GraphMatching G(n);
G.AddEdge(x, y, w);
auto [res, mat] = G.solve();

res 表示匹配的最大权。
mat[i] 表示和 i 匹配的点的编号。
若 i 不和任何点匹配，mat[i] = 0。
*/
struct Weighted_GraphMatching {
	struct Q { 
		int u, v, w;
	};
	int n, m, id, N;
	vector<vector<Q>> e;
	vector<vector<int>> b, p;
	vector<int> lab, lk, sl, st, f, s, ed, q;
	int h, t;
	Weighted_GraphMatching(int n) : n(n), m(n), id(0), N(2 * n + 5),
	e(N + 1, vector<Q>(N + 1, Q{0, 0, 0})), b(N + 1, vector<int>(N + 1)),
	p(N + 1), lab(N + 1), lk(N + 1), sl(N + 1), st(N + 1), 
	f(N + 1), s(N + 1), ed(N + 1), q(N + 1) {}
	#define all(x) (x).begin(), (x).end()

	vector<array<int, 3>> edge;
	void AddEdge(int x, int y, int w) {
		edge.push_back({x, y, w});
	}

	int d(Q x) {
		return lab[x.u] + lab[x.v] - e[x.u][x.v].w * 2;
	}
	void upd(int u, int v) {
		if (!sl[v] || d(e[u][v]) < d(e[sl[v]][v])) {
			sl[v] = u;
		}
	} 
	void ss(int v) {
		sl[v] = 0;
		for (int u = 1; u <= n; u++) {
			if (e[u][v].w > 0 && st[u] != v && !s[st[u]]) {
				upd(u, v);
			}
		}
	}
	void ins(int u) {
		if (u <= n) {
			q[++t] = u;
		} else {
			for (auto v : p[u]) {
				ins(v);
			}
		}
	}
	void mdf(int u, int w) {
		st[u] = w;
		if (u > n) {
			for (auto v : p[u]) {
				mdf(v, w);
			}
		}
	}
	int gr(int u, int v) {
		v = find(all(p[u]), v) - p[u].begin();
		if (v & 1) {
			reverse(1 + all(p[u]));
			return (int)p[u].size() - v;
		}
		return v;
	}
	void stm(int u, int v) {
		lk[u] = e[u][v].v;
		if (u <= n) {
			return ;
		}
		Q w = e[u][v];
		int x = b[u][w.u];
		int y = gr(u, x);
		for (int i = 0; i < y; i++) {
			stm(p[u][i], p[u][i ^ 1]);
		}
		stm(x, v);
		rotate(p[u].begin(), y + all(p[u]));
	}
	void aug(int u, int v) {
		int w = st[lk[u]];
		stm(u, v);
		if (!w) {
			return ;
		}
		stm(w, st[f[w]]);
		aug(st[f[w]], w);
	}
	int lca(int u, int v) {
		for (++id; u | v; swap(u, v)) {
			if (!u) {
				continue;
			}
			if (ed[u] == id) {
				return u;
			}
			ed[u] = id;
			u = st[lk[u]];
			if (u) {
				u = st[f[u]];
			}
		}
		return 0;
	}
	void add(int u, int a, int v) {
		int x = n + 1;
		while (x <= m && st[x]) {
			x++;
		}
		if (x > m) {
			m++;
		}
		lab[x] = s[x] = st[x] = 0;
		lk[x] = lk[a];
		p[x].clear();
		p[x].push_back(a);
		for (int i = u, j; i != a; i = st[f[j]]) {
			p[x].push_back(i);
			p[x].push_back(j = st[lk[i]]);
			ins(j);
		}
		reverse(1 + all(p[x]));
		for (int i = v, j; i != a; i = st[f[j]]) {
			p[x].push_back(i);
			p[x].push_back(j = st[lk[i]]);
			ins(j);
		}
		mdf(x, x);
		for (int i = 1; i <= m; i++) {
			e[x][i].w = e[i][x].w = 0;
		}
		for (int i = 1; i <= n; i++) {
			b[x][i] = 0;
		}
		for (auto u : p[x]) {
			for (int v = 1; v <= m; v++) {
				if (!e[x][v].w || d(e[u][v]) < d(e[x][v])) {
					e[x][v] = e[u][v];
					e[v][x] = e[v][u];
				}
			}
			for (int v = 1; v <= n; v++) {
				if (b[u][v]) {
					b[x][v] = u;
				}
			}
		}
		ss(x);
	}
	void ex(int u) {
		for (auto x : p[u]) {
			mdf(x, x);
		}
		int a = b[u][e[u][f[u]].u];
		int r = gr(u, a);
		for (int i = 0; i < r; i += 2) {
			int x = p[u][i];
			int y = p[u][i + 1];
			f[x] = e[y][x].u;
			s[x] = 1;
			s[y] = 0;
			sl[x] = 0;
			ss(y);
			ins(y);
		}
		s[a] = 1;
		f[a] = f[u];
		for (int i = r + 1; i < p[u].size(); i++) {
			s[p[u][i]] = -1;
			ss(p[u][i]);
		}
		st[u] = 0;
	}
	bool on(const Q &e) {
		int u = st[e.u];
		int v = st[e.v];
		int a;
		if (s[v] == -1) {
			f[v] = e.u;
			s[v] = 1;
			a = st[lk[v]];
			sl[v] = sl[a] = s[a] = 0;
			ins(a);
		} else if (!s[v]) {
			a = lca(u, v);
			if (!a) {
				aug(u, v);
				aug(v, u);
				return true;
			} else {
				add(u, a, v);
			}
		}
		return false;
	}
	bool bfs() {
		for (int i = 1; i <= m; i++) {
			s[i] = -1;
			sl[i] = 0;
		}
		h = 1;
		t = 0;
		for (int i = 1; i <= m; i++) {
			if (st[i] == i && !lk[i]) {
				f[i] = s[i] = 0;
				ins(i);
			}
		}
		if (h > t) {
			return 0;
		}
		while (true) {
			while (h <= t) {
				int u = q[h++];
				if (s[st[u]] != -1) {
					for (int v = 1; v <= n; v++) {
						if (e[u][v].w > 0 && st[u] != st[v]) {
							if (d(e[u][v])) {
								upd(u, st[v]);
							} else if (on(e[u][v])) {
								return true;
							}
						}
					}
				}
			}
			int x = inf;
			for (int i = n + 1; i <= m; i++) {
				if (st[i] == i && s[i] == 1) {
					x = min(x, lab[i] >> 1);
				}
			}
			for (int i = 1; i <= m; i++) {
				if (st[i] == i && sl[i] && s[i] != 1) {
					x = min(x, d(e[sl[i]][i]) >> s[i] + 1);
				}
			}
			for (int i = 1; i <= n; i++) {
				if (~s[st[i]]) {
					lab[i] += (s[st[i]] * 2 - 1) * x;
					if (lab[i] <= 0) {
						return 0;
					}
				}
			}
			for (int i = n + 1; i <= m; i++) {
				if (st[i] == i && ~s[st[i]]) {
					lab[i] += (2 - s[st[i]] * 4) * x;
				}
			}
			h = 1;
			t = 0;
			for (int i = 1; i <= m; i++) {
				if (st[i] == i && sl[i] && st[sl[i]] != i 
					&& !d(e[sl[i]][i]) && on(e[sl[i]][i])) {
					return true;
				}
			}
			for (int i = n + 1; i <= m; i++) {
				if (st[i] == i && s[i] == 1 && !lab[i]) {
					ex(i);
				}
			}
		}
		return 0;
	}
	pair<int, vector<int>> solve() {
		iota(st.begin(), st.end(), 0);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				e[i][j] = {i, j, 0};
			}
		}
		int wm = 0;
		for (auto [u, v, w] : edge) {
			e[u][v].w = e[v][u].w = max(e[u][v].w, w); 
			wm = max(wm, e[u][v].w);
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				b[i][j] = i * (i == j);
			}
		}
		for (int i = 1; i <= n; i++) {
			lab[i] = wm;
		}
		while (bfs());
		int res = 0;
		for (int i = 1; i <= n; i++) {
			if (lk[i]) {
				res += e[i][lk[i]].w;
			}
		}
		res /= 2;
		return {res, lk};
	};
	#undef all
};