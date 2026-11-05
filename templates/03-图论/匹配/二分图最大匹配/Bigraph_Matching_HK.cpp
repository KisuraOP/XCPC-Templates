/*
相比 Dinic 做法拥有更小的常数。
HK G(n, m); n 是左部点数，m 是右部点数。
G.add(x, y); 连接第 x 个左部点和第 y 个右部点。
int ans = G.solve();
*/
struct HK {
	vector<vector<int>> adj;
	vector<int> ml, mr, dis, cur, q, vs;
	HK(int n, int m) : adj(n + 1), ml(n + 1), mr(m + 1),
	dis(n + 1), cur(n + 1), q(n) {}
	void add(int x, int y) {
		if (adj[x].empty()) {
			vs.push_back(x);
		}
		adj[x].push_back(y);
	}
	int bfs() {
		int l = 0, r = 0;
		dis[0] = -1;
		for (auto i : vs) {
			cur[i] = 0;
			dis[i] = ml[i] ? -1 : 0;
			if (!ml[i]) {
				q[r++] = i;
			}
		}
		while (l < r) {
			int x = q[l++];
			if (dis[0] != -1 && dis[x] >= dis[0]) {
				continue;
			}
			for (auto y : adj[x]) {
				int z = mr[y];
				if (dis[z] == -1) {
					dis[z] = dis[x] + 1;
					if (z) {
						q[r++] = z;
					}
				}
			}
		}
		return dis[0] != -1;
	}
	int dfs(int x) {
		for (int &i = cur[x]; i < adj[x].size(); i++) {
			int y = adj[x][i];
			int z = mr[y];
			if (dis[z] == dis[x] + 1 && (!z || dfs(z))) {
				ml[x] = y;
				mr[y] = x;
				return true;
			}
		}
		dis[x] = -1;
		return false;
	}
	int solve() {
		int ans = 0;
		for (auto x : vs) {
			for (auto y : adj[x]) {
				if (!mr[y]) {
					ml[x] = y;
					mr[y] = x;
					ans++;
					break;
				}
			}
		}
		while (bfs()) {
			for (auto i : vs) {
				if (!ml[i]) {
					ans += dfs(i);
				}
			}
		}
		return ans;
	}
};
