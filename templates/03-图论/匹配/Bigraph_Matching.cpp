/*
二分图最大匹配, 增广路算法, O(n+m+ne)。
n 是左部点数, m 是右部点数, e 是边数。

邻接表存的是左部点指向右部点的有向边。
mat[i] 表示与右部点 i 匹配的左部点编号。

另有最大流做法: (S, i, 1), (n + i, T, 1), (x, n + y, 1)。 
*/
vector<int> vis(m + 1), mat(m + 1);
int tim = 0;
auto dfs = [&] (auto self, int x) -> int {
	for (auto y : adj[x]) {
		if (vis[y] != tim) {
			vis[y] = tim;
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
	tim++;
	ans += dfs(dfs, i);
}