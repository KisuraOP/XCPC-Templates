/*
小根 (i, a[i]) 笛卡尔树
*/

vector<int> ls(n + 1), rs(n + 1);
vector<int> stk(n + 1);
for (int i = 1, top = 0; i <= n; i++) {
	int p = top;
	while (p > 0 && a[stk[p]] > a[i]) { // 符号改为 < 即为大根
		p--;
	}
	if (p > 0) {
		rs[stk[p]] = i;
	}
	if (p < top) {
		ls[i] = stk[p + 1];
	}
	stk[++p] = i;
	top = p;
}
vector<vector<int>> adj(n + 1);
for (int i = 1; i <= n; i++) {
	if (ls[i] > 0) {
		adj[i].push_back(ls[i]);
	}
	if (rs[i] > 0) {
		adj[i].push_back(rs[i]);
	}
}