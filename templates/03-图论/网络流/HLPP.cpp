/*
HLPP G(n, 0, S, T);
n 为顶点数，S 为源点编号，T 为汇点编号。

G.Add(u, v, cap);
连一条 u -> v 容量为 cap 的有向边。

int flow = G.GetMaxFlow();
获取最大流
*/

class HLPP {
	public:
		typedef long long T;
		class edge {
			public:
				int to, nex;
				T flow;
				edge(int to, T flow, int nex): to(to), flow(flow), nex(nex) {}
				edge() {}
		};
		int n, m, s, t, maxh, maxgaph, workcnt;
		vector<vector<edge>> vec;
		vector<T> ov;
		vector<int> h, cur, ovlist, ovnex, gap, gappre, gapnex;
		HLPP(int n, int m, int s, int t): n(n), m(m), s(s), t(t), maxh(0), maxgaph(0), workcnt(0),
			vec(n + 1), ov(n + 1), h(n + 1), cur(n + 1),
			ovlist((n + 1), -1), ovnex((n + 1), -1),
			gap((n + 1), -1), gappre((n + 1), -1), gapnex((n + 1), -1) {}
		HLPP() {}
		void PushFlow(int u, edge &e, T flow) {
			if (!(ov[e.to]) && (e.to) != t) {
				ovnex[e.to] = ovlist[h[e.to]];
				ovlist[h[e.to]] = (e.to);
			}
			ov[u] -= flow;
			ov[e.to] += flow;
			e.flow -= flow;
			vec[e.to][e.nex].flow += flow;
		}
		void SetHeight(int u, int newh) {
			if (~gappre[u]) {
				if (gappre[u] == u) {
					gap[h[u]] = gapnex[u];
					gappre[gapnex[u]] = gapnex[u];
				} else {
					gapnex[gappre[u]] = gapnex[u];
					if (~gapnex[u]) {
						gappre[gapnex[u]] = gappre[u];
					}
				}
			}
			if ((h[u] = newh) >= n) {
				return;
			}
			maxgaph = max(maxgaph, newh);
			if (ov[u]) {
				maxh = max(maxh, newh);
				ovnex[u] = ovlist[newh];
				ovlist[newh] = u;
			}
			if (~(gapnex[u] = gap[newh])) {
				gappre[gapnex[u]] = u;
			}
			gap[newh] = gappre[u] = u;
		}
		void UpdateNode(int u) {
			int nh = n, sz = vec[u].size();
			for (int i = cur[u]; i < sz; i++) {
				edge &e = vec[u][i];
				if (e.flow) {
					if (h[e.to] + 1 == h[u]) {
						PushFlow(u, e, min(ov[u], e.flow));
						if (!ov[u]) {
							cur[u] = i;
							return;
						}
					} else {
						nh = min(nh, h[e.to] + 1);
					}
				}
			}
			for (int i = 0; i < cur[u]; i++) {
				edge &e = vec[u][i];
				if (e.flow) {
					nh = min(nh, h[e.to] + 1);
				}
			}
			cur[u] = 0;
			workcnt++;
			if (~gapnex[gap[h[u]]]) {
				SetHeight(u, nh);
			} else {
				int oldh = h[u];
				for (int i = oldh; i <= maxgaph; i++) {
					for (int j = gap[i]; ~j; j = gapnex[j]) {
						h[j] = n;
					}
					gap[i] = -1;
				}
				maxgaph = oldh - 1;
			}
		}
		void GlobalRelabel() {
			maxgaph = maxh = workcnt = 0;
			fill(h.begin(), h.end(), n), h[t] = 0;
			fill(gap.begin(), gap.end(), -1);
			fill(gappre.begin(), gappre.end(), -1);
			fill(gapnex.begin(), gapnex.end(), -1);
			fill(ovlist.begin(), ovlist.end(), -1);
			fill(ovnex.begin(), ovnex.end(), -1);
			fill(cur.begin(), cur.end(), 0);
			vector<int> q;
			q.assign(n + 1, 0);
			int front = 0, back = -1;
			for (q[++back] = t; front <= back; ) {
				int u = q[front++];
				int het = h[u] + 1;
				for (auto &e : vec[u]) {
					int v = e.to;
					if (vec[v][e.nex].flow && h[v] == n && e.to != s) {
						SetHeight(v, het);
						q[++back] = v;
					}
				}
			}
		}
		void Add(int from, int to, T flow) {
			vec[from].push_back(edge(to, flow, vec[to].size()));
			vec[to].push_back(edge(from, 0, vec[from].size() - 1));
		}
		T GetMaxFlow() {
			GlobalRelabel();
			for (auto &e : vec[s]) {
				if (e.flow) {
					PushFlow(s, e, e.flow);
					maxh = max(maxh, h[e.to]);
				}
			}
			for ( ; maxh; maxh--) {
				while (~ovlist[maxh]) {
					int u = ovlist[maxh];
					ovlist[maxh] = ovnex[u];
					UpdateNode(u);
					if (workcnt >= (n << 2)) {
						GlobalRelabel();
					}
				}
			}
			return ov[t];
		}
};