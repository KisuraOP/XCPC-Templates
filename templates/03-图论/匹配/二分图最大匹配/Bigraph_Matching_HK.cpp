/*
相比 Dinic 做法拥有更小的常数。
HK G(n, m); n 是左部点数，m 是右部点数。
G.add(x, y); 连接第 x 个左部点和第 y 个右部点。
int ans = G.solve();

ml[x] 表示第 x 个左部点匹配的右部点编号，0 表示未匹配。
mr[y] 表示第 y 个右部点匹配的左部点编号，0 表示未匹配。
*/
struct HK {
	vector<pair<int, int>> adj, ed;
	vector<int> e, ml, mr, dis, cur, q, vs;
	HK(int n, int m) : adj(n + 1), ml(n + 1), mr(m + 1),
	dis(n + 1), cur(n + 1), q(n) {}
	void add(int x, int y) {
		if (!adj[x].second++) {
			vs.push_back(x);
		}
		ed.push_back({x, y});
	}
	int bfs(bool aug = false) {
		int l = 0, r = 0, cnt = 0;
		for (auto i : vs) {
			dis[i] = ml[i] ? -1 : aug ? i : 0;
			if (!ml[i]) {
				cur[i] = aug ? 0 : adj[i].first;
				q[r++] = i;
			}
		}
		while (l < r) {
			int x = q[l++];
			if (aug && ml[dis[x]]) {
				continue;
			}
			for (int i = adj[x].first; i < adj[x].second; i++) {
				int y = e[i], z = mr[y];
				if (!z) {
					cnt++;
					if (aug) {
						while (y) {
							mr[y] = x;
							swap(ml[x], y);
							x = cur[x];
						}
						break;
					}
				} else if (dis[z] == -1) {
					dis[z] = dis[x] + !aug;
					cur[z] = aug ? x : adj[z].first;
					q[r++] = z;
				}
			}
		}
		return cnt;
	}
	int dfs(int x) {
		int r = 0;
		q[r++] = x;
		while (r) {
			x = q[r - 1];
			if (cur[x] == adj[x].second) {
				dis[x] = -1;
				r--;
				continue;
			}
			int y = e[cur[x]++], z = mr[y];
			if (!z) {
				while (r) {
					x = q[--r];
					mr[y] = x;
					swap(ml[x], y);
					dis[x] = -1;
				}
				return true;
			}
			if (dis[z] == dis[x] + 1) {
				q[r++] = z;
			}
		}
		return false;
	}
	int solve() {
		int ans = 0, cnt = 0, d = 1;
		e.resize(ed.size());
		for (auto x : vs) {
			cur[x] = cnt;
			cnt += adj[x].second;
			adj[x] = {cur[x], cnt};
		}
		for (auto [x, y] : ed) {
			e[cur[x]++] = y;
		}
		for (int i = 0; d && i * i < vs.size(); i++) {
			d = bfs(true);
			ans += d;
		}
		while (d && bfs()) {
			for (auto i : vs) {
				if (!ml[i]) {
					ans += dfs(i);
				}
			}
		}
		return ans;
	}
};