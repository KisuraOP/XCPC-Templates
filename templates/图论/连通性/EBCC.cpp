/*
EBCC G(n);
n 为顶点数。

G.addEdge(x, y, w);
连一条 x -> y 边权为 w 的双向边。

vector<int> bel = G.work_point();
求点双连通分量，返回 bel 数组，bel[x] 代表 x 所在的点双连通分量编号。

vector<int> bel = G.work_edge();
求边双连通分量，返回 bel 数组，bel[x] 代表 x 所在的边双连通分量编号。

_node adj = G.shrinkPoint();
缩点，返回缩点后图的邻接表。

求割点：将第 3 行和函数 tarjan_point 内的注释取消，割点编号存在 cut 数组中。
求割边：将第 2 行和函数 tarjan_edge 内的注释取消，割边编号存在 E 数组中。
*/

#define _node vector<vector<array<int, 2>>> 
// set<array<int, 2>> E;
// set<int> cut;
struct EBCC {
	int n;
	_node adj;
	vector<vector<int>> scc;
	vector<int> dfn, low, stk, c;
	int tim = 0, top = 0, cnt = 0;
	EBCC() {}
	EBCC(int n) {
		init(n);
	}
	void init(int n) {
		this->n = n;
		adj.resize(n + 1, {});
		dfn.resize(n + 1);
		low.resize(n + 1);
		stk.resize(n + 1);
		c.resize(n + 1);
	}
	void addEdge(int x, int y, int w) {
		adj[x].push_back({y, w});
		adj[y].push_back({x, w});
	}
	void tarjan_point(int x, int par) {
		dfn[x] = low[x] = ++tim;
		stk[++top] = x;
		int son = 0;
		for (auto [y, _] : adj[x]) {
			if (!dfn[y]) {
				son++;
				tarjan_point(y, x);
				low[x] = min(low[x], low[y]);
				if (low[y] >= dfn[x]) {
					cnt++;
					scc.push_back({});
					while (stk[top + 1] != y) {
						scc[cnt].push_back(stk[top--]);
					}
					scc[cnt].push_back(x);
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
			scc.push_back({});
			scc[cnt].push_back(x);
		}
	}
	vector<int> work_point() {
		scc.push_back({});
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) tarjan_point(i, 0);
		}
		return c;
	}
	void tarjan_edge(int x, int par) {
		dfn[x] = low[x] = ++tim;
		stk[++top] = x;
		for (auto [y, _] : adj[x]) {
			if (y == par) continue;
			if (!dfn[y]) {
				tarjan_edge(y, x);
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
	vector<int> work_edge() {
		scc.push_back({});
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) tarjan_edge(i, 0);
		}
		return c;
	}
	_node shrinkPoint() {
		_node Adj(n + 1);
		for (int x = 1; x <= n; x++) {
			for (auto [y, w] : adj[x]) {
				if (c[x] == c[y]) continue;
				Adj[c[x]].push_back({c[y], w});
			}
		}
		return Adj;
	}
};