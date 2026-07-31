#include <bits/stdc++.h>
using namespace std;
#define fre(x) freopen(#x".in", "r", stdin); freopen(#x".out", "wb", stdout)
#define ck(x)  { cout << "check " << x << endl;}
#define int long long
#define double long double
#define inf 0x3fffffffffffffff

struct SegTree {
	int n;
	vector<double> mx;
	SegTree(int sz) {
		n = sz;
		mx.assign(4 * n + 5, 0);
	}
	void pushup(int p) {
		mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
	}
	void update(int p, int l, int r, int pos, double x) {
		if (l == r) {
			mx[p] = x;
			return ;
		}
		int mid = l + r >> 1;
		if (pos <= mid) {
			update(p << 1, l, mid, pos, x);
		} else {
			update(p << 1 | 1, mid + 1, r, pos, x);
		}
		pushup(p);
	} 
	void update(int pos, double x) {
		update(1, 1, n, pos, x);
	}
	double query(int p, int l, int r, int pos) {
		if (l == r) {
			return mx[p];
		}
		int mid = l + r >> 1;
		if (pos <= mid) {
			return query(p << 1, l, mid, pos);
		} else {
			return query(p << 1 | 1, mid + 1, r, pos);
		}
	}
	double query(int pos) {
		return query(1, 1, n, pos);
	}
};


//-------------- templates above --------------


void solve() {
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<array<int, 2>>> adj(n + 1);
	vector<array<int, 2>> E(m + 1);
	for (int i = 1; i <= m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		adj[x].push_back({y, w});
		E[i] = {x, y};
	}
	vector d(n + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; i++) {
		vector<int> dis(n + 1, inf), vis(n + 1);
		auto dijkstra = [&] (int S) {
			using P = array<int, 2>;
			priority_queue<P, vector<P>, greater<P>> Q;
			Q.push({0, S});
			dis[S] = 0;
		
			while (!Q.empty()) {
				auto [dist, x] = Q.top();
				Q.pop();
				if (vis[x]) {
					continue;
				}
				vis[x] = true;
		
				for (auto [y, w] : adj[x]) {
					if (dis[y] > dist + w) {
						dis[y] = dist + w;
						Q.push({dis[y], y});
					}
				}
			}
		};
		dijkstra(i);
		d[i] = dis;
	}
	SegTree seg(m);
	for (int i = 1; i <= m; i++) {
		auto [x, y] = E[i];
		double res = max(1.0L * d[x][y] / d[y][x], 1.0L * d[y][x] / d[x][y]);
		seg.update(i, res);
	}
	while (q--) {
		int k, w;
		cin >> k >> w;
		auto [u, v] = E[k];
		vector<int> ori(m + 1);
		for (int i = 1; i <= m; i++) {
			auto [x, y] = E[i];
			ori[i] = seg.query(i);
			double dxy = min(d[x][y], d[x][u] + w + d[v][y]);
			double dyx = min(d[y][x], d[y][u] + w + d[v][x]);
			seg.update(i, max(1.0L * dxy / dyx, 1.0L * dyx / dxy));
		}
		double ans = seg.mx[1];
		cout << fixed << setprecision(10) << ans << "\n";
		for (int i = 1; i <= m; i++) {
			seg.update(i, ori[i]);
		}
	}
}


signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}