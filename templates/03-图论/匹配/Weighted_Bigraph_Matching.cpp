/*
二分图最大权匹配, KM 算法, O(n^3)。

KM G(nl, nr);
G.addEdge(x, y, w);
int res = G.solve();

G.fl[i] 表示和左部点 i 匹配的右部点编号。
若 i 不与任何右部点匹配, G.fl[i] = 0。

注意, 若需要处理负权边, 正确的方式是: 
先给所有边边权加上 N = 1e12, 最后答案减去 (匹配数 * N)。

另有费用流方法, 但容易被卡: 
(S, 1 ~ nl, 1, 0), (nl + 1 ~ nl + nr, T, 1, 0)
(1 ~ nl, T, 1, 0), (x, nl + y, 1, -w)
*/
struct KM {
	int n;
	vector<vector<int>> G;
	vector<int> hl, hr, dt, fl, fr, vl, vr, pre, q;
	int ql, qr;
	KM(int nl, int nr) : n(max(nl, nr)), G(n + 1, vector<int>(n + 1)),
	hl(n + 1), hr(n + 1), dt(n + 1), fl(n + 1), fr(n + 1),
	vl(n + 1), vr(n + 1), pre(n + 1), q(n + 1), ql(0), qr(0) {}

	void addEdge(int x, int y, int w) {
		G[x][y] = max(G[x][y], w);
	}
	bool check(int i) {
		vl[i] = 1;
		if (fl[i] != -1) {
			vr[fl[i]] = 1;
			q[qr++] = fl[i];
			return true;
		}
		while (i != -1) {
			int j = pre[i];
			int nxt = fr[j];
			fl[i] = j;
			fr[j] = i;
			i = nxt;
		}
		return false;
	}
	void bfs(int s) {
		for (int i = 1; i <= n; i++) {
			vl[i] = vr[i] = 0;
			dt[i] = inf;
		}
		ql = qr = 0;
		q[qr++] = s;
		vr[s] = 1;
		while (true) {
			while (ql < qr) {
				int j = q[ql++];
				for (int i = 1; i <= n; i++) {
					if (vl[i]) {
						continue;
					}
					int d = hl[i] + hr[j] - G[i][j];
					if (d <= dt[i]) {
						pre[i] = j;
						if (d) {
							dt[i] = d;
						} else if (!check(i)) {
							return ;
						}
					}
				}
			}
			int d = inf;
			for (int i = 1; i <= n; i++) {
				if (!vl[i]) {
					d = min(d, dt[i]);
				}
			}
			for (int i = 1; i <= n; i++) {
				if (vl[i]) {
					hl[i] += d;
				} else {
					dt[i] -= d;
				}
				if (vr[i]) {
					hr[i] -= d;
				}
			}
			for (int i = 1; i <= n; i++) {
				if (!vl[i] && !dt[i] && !check(i)) {
					return ;
				}
			}
		}
	}
	int solve() {
		for (int i = 1; i <= n; i++) {
			fl[i] = fr[i] = -1;
			hl[i] = *max_element(G[i].begin() + 1, G[i].end());
		}
		for (int i = 1; i <= n; i++) {
			bfs(i);
		}
		int res = 0;
		for (int i = 1; i <= n; i++) {
			if (G[i][fl[i]]) {
				res += G[i][fl[i]];
			} else {
				fl[i] = 0;
			}
		}
		return res;
	}
};