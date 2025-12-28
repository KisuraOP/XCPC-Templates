vector<int> dfn(n + 1), low(n + 1), stk(n + 1), c(n + 1);
vector<bool> vis(n + 1);
vector<vector<int>> scc(n + 1);
int tim = 0, top = 0, cnt = 0;
//c[x]: the id of BCC which x belongs to
//cnt : the numbers of BCCs in whole graph
//scc[i] : the id of nodes belongs to the i-th BCC
auto tarjan = [&] (auto self, int x) -> void {
	dfn[x] = low[x] = ++tim;
	vis[x] = true;
	stk[++top] = x;
	for (auto y : adj[x]) {
		if (!dfn[y]) {
			self(self, y);
			low[x] = min(low[x], low[y]);
		} else if (vis[y]) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	if (dfn[x] == low[x]) {
		int now; ++cnt;
		do {
			now = stk[top--];
			vis[now] = false;
			c[now] = cnt;
			scc[cnt].push_back(now);
		} while(x != now);
	}
};
vector<int> rd(n + 1);
vector<vector<int>> Adj(n + 1);
auto shrinkPoint = [&]() {
	for (int x = 1; x <= n; x++) {
		for (auto y : adj[x]) {
			if (c[x] == c[y]) continue;
			Adj[c[x]].push_back(c[y]);
			rd[c[y]]++;
		}
	}
};

for (int i = 1; i <= n; i++) {
	if (!dfn[i]) {
		tarjan(tarjan, i);
	}
}
shrinkPoint();