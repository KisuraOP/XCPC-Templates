/*
能够处理自环和重边。
*/

// set<int> cut;
struct vBCC {
	int n;
	vector<vector<int>> adj, scc, c;
	vector<int> dfn, low, stk;
	int tim, top, cnt;

	vBCC(int _n) : n(_n), adj(n + 1), dfn(n + 1), low(n + 1), 
	stk(n + 5), c(n + 1), tim(0), top(0), cnt(0) {}

	void addEdge(int x, int y) {
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	void tarjan_Node(int x, int par) {
		dfn[x] = low[x] = ++tim;
		stk[++top] = x;
		int son = 0;
		for (auto y : adj[x]) {
			if (!dfn[y]) {
				son++;
				tarjan_Node(y, x);
				low[x] = min(low[x], low[y]);
				if (low[y] >= dfn[x]) {
					cnt++;
					scc.push_back({});
					while (stk[top + 1] != y) {
						int z = stk[top--];
						scc[cnt].push_back(z);
						c[z].push_back(cnt);
					}
					scc[cnt].push_back(x);
					c[x].push_back(cnt);
				}
				/*
				if (par && low[y] >= dfn[x]) {
					cut.insert(x);
				}
				*/
			} else if (y != par) {
				low[x] = min(low[x], dfn[y]);
			}
		}
		/*
		if (!par && son >= 2) {
			cut.insert(x);
		}
		*/
		if (par == 0 && son == 0) {
			cnt++;
			scc.push_back({x});
			c[x].push_back(cnt);
			top = 0;
		}
	}
	void work_Node() {
		scc.push_back({});
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) tarjan_Node(i, 0);
		}
	}
};