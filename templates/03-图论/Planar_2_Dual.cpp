const double eps = 1e-8;

struct P {
	int x, y;
	P() : x(0), y(0) {}
	P(int _x, int _y) : x(_x), y(_y) {}
	friend P operator + (const P &a, const P &b) {
		return P(a.x + b.x, a.y + b.y);
	}
	friend P operator - (const P &a, const P &b) {
		return P(a.x - b.x, a.y - b.y);
	}
	friend P operator * (const P &a, const int &b) {
		return P(a.x * b, a.y * b);
	}
	friend P operator * (const int &a, const P &b) {
		return P(a * b.x, a * b.y);
	}
	bool operator < (const P &oth) const {
		if (x != oth.x) {
			return x < oth.x;
		}
		return y < oth.y;
	}
};

// 平面图转对偶图 O(n + m log n)
// 给定的平面图不能有重边。
// 1-index
struct Planar2Dual {
	// 平面图
	int n;
	vector<P> a; // 点坐标
	vector<vector<int>> adj;

	// 对偶图
	int cnt = 0; // 面数
	int rt = -1; // 无限面编号
	vector<vector<int>> face; // 面边界的点；多个边界依次拼接
	vector<vector<int>> Adj;

	Planar2Dual(const vector<P> &_a, const vector<vector<int>> &_adj)
	: n(_a.size() - 1), a(_a), adj(_adj) {
		work();
	}
	int ID(const int &x, const int &y) {
		return (x << 30) | y;
	}
	void work() {
		for (int i = 1; i <= n; i++) {
			sort(adj[i].begin(), adj[i].end(), [&] (const int &A, const int &B) {
				P u = a[A] - a[i], v = a[B] - a[i];
				bool p = u.y > 0 || (u.y == 0 && u.x > 0);
				bool q = v.y > 0 || (v.y == 0 && v.x > 0);
				if (p != q) return p > q;
				return u.x * v.y - u.y * v.x > 0;
			});
		}
		// vector<unordered_map<int, int>> nxt(n + 1);
		vector<map<int, int>> nxt(n + 1);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < adj[i].size(); j++) {
				int x = adj[i][j];
				int y = adj[i][(j - 1 + adj[i].size()) % adj[i].size()];
				nxt[i][x] = y;
			}
		}
		// unordered_map<int, int> vis;
		map<int, int> vis;
		map<int, vector<int>> face_id;
		face.push_back({});
		for (int x = 1; x <= n; x++) {
			for (auto y : adj[x]) {
				if (vis[ID(x, y)]) {
					continue;
				}
				cnt++;
				int u = x;
				int v = y;
				vector<int> path;
				while (!vis[ID(u, v)]) {
					vis[ID(u, v)] = cnt;
					path.push_back(u);
					face_id[ID(min(u, v), max(u, v))].push_back(cnt);
					int t = nxt[v][u];
					u = v;
					v = t;
				}
				face.push_back(path);
			}
		}
		vector<int> par(cnt + 1), who;
		iota(par.begin(), par.end(), 0);
		auto get = [&] (auto self, int x) -> int {
			return par[x] == x ? x : par[x] = self(self, par[x]);
		};
		vector<array<int, 2>> seg;
		vector<array<int, 3>> evt;
		for (int u = 1; u <= n; u++) {
			for (auto v : adj[u]) if (u < v && a[u].x != a[v].x) {
				int x = u, y = v, k = seg.size();
				if (a[y] < a[x]) swap(x, y);
				seg.push_back({x, y});
				who.push_back(0);
				evt.push_back({a[x].x, 2, k});
				evt.push_back({a[y].x, 1, k});
			}
		}
		for (int i = 1; i <= cnt; i++) {
			int area = 0;
			for (int j = 0; j < face[i].size(); j++) {
				P p1 = a[face[i][j]];
				P p2 = a[face[i][(j + 1) % face[i].size()]];
				area += p1.x * p2.y - p2.x * p1.y;
			}
			if (area <= 0) {
				int x = face[i][0], k = seg.size();
				for (auto y : face[i]) if (a[y] < a[x]) x = y;
				seg.push_back({x, x});
				who.push_back(i);
				evt.push_back({a[x].x, 0, k});
			}
		}
		// 在每个分量最左点的左侧，向下找包含它的面。
		auto cross = [&] (P u, P v) { return u.x * v.y - u.y * v.x; };
		auto cmp = [&] (int i, int j) {
			auto [u, v] = seg[i];
			auto [x, y] = seg[j];
			int z;
			if (a[u].x < a[x].x) {
				z = cross(a[v] - a[u], a[x] - a[u]);
				if (z) return z > 0;
			} else if (a[u].x > a[x].x) {
				z = cross(a[y] - a[x], a[u] - a[x]);
				if (z) return z < 0;
			} else if (a[u].y != a[x].y) {
				return a[u].y < a[x].y;
			}
			z = cross(a[v] - a[u], a[y] - a[x]);
			return z ? z > 0 : i < j;
		};
		set<int, decltype(cmp)> st(cmp);
		sort(evt.begin(), evt.end());
		for (auto [_, t, k] : evt) {
			if (t == 2) st.insert(k);
			else if (t == 1) st.erase(k);
			else {
				auto it = st.lower_bound(k);
				int f = 0;
				if (it != st.begin()) {
					auto [u, v] = seg[*--it];
					f = vis[ID(u, v)];
				}
				par[get(get, who[k])] = get(get, f);
			}
		}
		vector<int> id(cnt + 1);
		int tot = 0;
		for (int i = 0; i <= cnt; i++) {
			int x = get(get, i);
			if (!id[x]) id[x] = ++tot;
		}
		vector<vector<int>> F(tot + 1);
		for (int i = 1; i <= cnt; i++) {
			auto &v = F[id[get(get, i)]];
			v.insert(v.end(), face[i].begin(), face[i].end());
		}
		face = move(F);
		cnt = tot;
		rt = id[get(get, 0)];
		Adj.assign(cnt + 1, {});
		for (auto [_, v] : face_id) {
			if (v.size() == 2) {
				int x = id[get(get, v[0])];
				int y = id[get(get, v[1])];
				Adj[x].push_back(y);
				Adj[y].push_back(x);
			}
		}
		for (int i = 1; i <= cnt; i++) {
			sort(Adj[i].begin(), Adj[i].end());
			Adj[i].erase(unique(Adj[i].begin(), Adj[i].end()), Adj[i].end());
		}
	}
};