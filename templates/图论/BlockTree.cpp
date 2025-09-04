/*
BlockTree G(n);
n 为顶点数。

G.add(x, y);
连一条 x 和 y 间的双向边。

vector<vector<int>> adj = G.work();
建立给定图的圆方树，返回相应邻接表。

方点从 n + 1 开始编号。
*/

struct BlockTree {
	int n, cnt;
	vector<vector<int>> adj, Adj;
	vector<int> dfn, low, stk;
	int tim = 0, top = 0;
	BlockTree(int n) {
		this->n = n;
		cnt = n;
		adj.resize(n + 1, {});
		Adj.resize(2 * n + 1, {});
		dfn.resize(n + 1);
		low.resize(n + 1);
		stk.resize(n + 1);
	}
	void add(int x, int y) {
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	void Add(int x, int y) {
		// cout << "(" << x << " -> " << y << ")\n";
		Adj[x].push_back(y);
		Adj[y].push_back(x);
	}
	void tarjan(int x) {
		dfn[x] = low[x] = ++tim;
		stk[++top] = x;
		for (auto y : adj[x]) {
			if (!dfn[y]) {
				tarjan(y);
				low[x] = min(low[x], low[y]);
				if (low[y] == dfn[x]) {
					int now; cnt++;
					do {
						now = stk[top--];
						Add(cnt, now);
					} while (now != y);
					Add(cnt, x);
				}
			} else {
				low[x] = min(low[x], dfn[y]);
			}
		}
	}
	vector<vector<int>> work() {
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) {
				tarjan(i);
			}
		}
		return Adj;
	} 
};