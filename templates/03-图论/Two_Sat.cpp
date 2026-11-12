/*
TwoSat ts(n);
n 为变元数量。

ts.addbind(x1, t1, x2, t2);
添加一条限制："x1 = t1" 或 "x2 = t2"。

bool ok = ts.work();
判断这些限制能否同时满足。
若能满足，ts.ans[i] 为变量 xi 在一组可行解中的取值。
图中点 i、i + n 分别表示 xi = 0、xi = 1。
*/

struct TwoSat {
	int n;
	vector<vector<int>> adj;
	vector<int> ans;
	TwoSat(int n) {
		this->n = n;
		adj.resize(2 * n + 1);
		ans.resize(n + 1);
	}
	void addbind(int x, bool ok1, int y, bool ok2) {
		adj[x + n * (!ok1)].push_back(y + n * ok2);
		adj[y + n * (!ok2)].push_back(x + n * ok1);
	}
	bool work() {
		vector<int> dfn(2 * n + 1), low(2 * n + 1);
		vector<int> stk(2 * n + 1), c(2 * n + 1);
		vector<bool> vis(2 * n + 1, false);
		int tim = 0, top = 0, cnt = 0;
		function<void(int)> tarjan = [&](int x) {
			dfn[x] = low[x] = ++tim;
			vis[x] = true;
			stk[++top] = x;
			for (auto y : adj[x]) {
				if (!dfn[y]) {
					tarjan(y);
					low[x] = min(low[x], low[y]);
				} else if (vis[y]) {
					low[x] = min(low[x], dfn[y]);
				}
			}
			if (dfn[x] == low[x]) {
				int now;
				++cnt;
				do{
					now = stk[top--];
					vis[now] = false;
					c[now] = cnt;
				} while (x != now);
			}
		};
		for (int i = 1; i <= 2 * n; i++) {
			if (!dfn[i]) {
				tarjan(i);
			}
		}
		for (int i = 1; i <= n; i++) {
			if (c[i] == c[i + n]) {
				return false;
			}
			ans[i] = c[i] > c[i + n] ? 1ll : 0ll;
		}
		return true;
	}
	vector<int> getans() {
		return ans;
	}
};