/*
二分图最大匹配, 增广路算法, O(ne)。
n 是左部点数, m 是右部点数, e 是边数。

邻接表存的是左部点指向右部点的有向边。
mat[i] 表示与右部点 i 匹配的左部点编号。

另有最大流做法: (S, i, 1), (n + i, T, 1), (x, y, 1)。 
*/
vector<int> vis(m + 1), mat(m + 1);
auto dfs = [&] (auto self, int x) -> int {
	for (auto y : adj[x]) {
		if (!vis[y]) {
			vis[y] = true;
			if (!mat[y] || self(self, mat[y])) {
				mat[y] = x;
				return true;
			}
		}
	}
	return false;
};
int ans = 0;
for (int i = 1; i <= n; i++) {
	vis.assign(m + 1, 0);
	ans += dfs(dfs, i);
}