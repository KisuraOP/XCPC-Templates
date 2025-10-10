// set<array<int, 2>> E;
struct eBCC {
	int n;
	vector<vector<array<int, 2>>> adj;
	vector<vector<int>> scc;
	vector<int> dfn, low, stk, c;
	int tim, top, cnt, eid;

	eBCC(int _n) : n(_n), adj(n + 1), dfn(n + 1), low(n + 1), 
	stk(n + 1), c(n + 1), tim(0), top(0), cnt(0), eid(0) {}

	void addEdge(int x, int y) {
		adj[x].push_back({y, ++eid});
		adj[y].push_back({x, eid});
	}
	void tarjan_Edge(int x, int par) {
		dfn[x] = low[x] = ++tim;
		stk[++top] = x;
		for (auto [y, e] : adj[x]) {
			if (e == par) continue;
			if (!dfn[y]) {
				tarjan_Edge(y, e);
				low[x] = min(low[x], low[y]);
				/*
				if (low[y] > dfn[x]) {
					E.insert({x, y});
				}
				*/
			} else if (!c[y] && dfn[y] < dfn[x]) {
				low[x] = min(low[x], dfn[y]);
			}
		}
		if (dfn[x] == low[x]) {
			int now; cnt++;
			scc.push_back({});
			do {
				now = stk[top--];
				c[now] = cnt;
				scc[cnt].push_back(now);
			} while (x != now);
		}
	}
	vector<int> work_Edge() {
		scc.push_back({});
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) tarjan_Edge(i, 0);
		}
		return c;
	}
	vector<vector<int>> shrinkPoint() {
		vector<vector<int>> Adj(n + 1);
		for (int x = 1; x <= n; x++) {
			for (auto [y, _] : adj[x]) {
				if (c[x] == c[y]) continue;
				Adj[c[x]].push_back(c[y]);
			}
		}
		return Adj;
	}
};