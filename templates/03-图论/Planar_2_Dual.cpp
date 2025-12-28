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

// 平面图转对偶图 O(m log n)
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
	vector<vector<int>> face; // 组成面的点的编号
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
				double r1 = atan2l((double)(a[A].y - a[i].y), (double)(a[A].x - a[i].x));
				double r2 = atan2l((double)(a[B].y - a[i].y), (double)(a[B].x - a[i].x));
				if (abs(r1 - r2) > eps) {
					return r1 < r2;
				}
				double d1 = (double)((a[A].x - a[i].x) * (a[A].x - a[i].x) + (a[A].y - a[i].y) * (a[A].y - a[i].y));
				double d2 = (double)((a[B].x - a[i].x) * (a[B].x - a[i].x) + (a[B].y - a[i].y) * (a[B].y - a[i].y));
				return d1 < d2;
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
					vis[ID(u, v)] = true;
					path.push_back(u);
					face_id[ID(min(u, v), max(u, v))].push_back(cnt);
					int t = nxt[v][u];
					u = v;
					v = t;
				}
				face.push_back(path);
			}
		}
		vector<int> inf_face(cnt + 1);
		for (int i = 1; i <= cnt; i++) {
			double area = 0;
			for (int j = 0; j < face[i].size(); j++) {
				P p1 = a[face[i][j]];
				P p2 = a[face[i][(j + 1) % face[i].size()]];
				area += (double)p1.x * (double)p2.y - (double)p2.x * (double)p1.y;
			}
			if (area <= 0) {
				rt = i;
				inf_face[i] = true;
			}
		}
		Adj.assign(cnt + 1, {});
		for (auto [_, v] : face_id) {
			if (v.size() == 2) {
				int x = v[0];
				int y = v[1];
				if (inf_face[x]) {
					x = rt;
				}
				if (inf_face[y]) {
					y = rt;
				}
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