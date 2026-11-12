/*
树上启发式合并的处理顺序：

- 先递归处理轻儿子，返回前清空统计结果。
- 再递归处理重儿子，保留统计结果。
- 加入当前点和各棵轻子树中的点，记录当前点的答案。

示例：对每个点，求其子树中出现次数最多的所有颜色的编号之和。
*/

vector<int> son(n + 1), sz(n + 1);
auto dfs1 = [&] (auto self, int x, int fa) -> void {
	sz[x] = 1;
	for (auto y : adj[x]) {
		if (y == fa) {
			continue;
		}
		self(self, y, x);
		sz[x] += sz[y];
		if (sz[y] > sz[son[x]]) {
			son[x] = y;
		}
	}
};
int sum = 0, mx = 0;
vector<int> cnt(n + 1), ans(n + 1);
auto calc = [&] (auto self, int x, int fa, int val, int p) -> void {
	cnt[col[x]] += val;
	if (cnt[col[x]] > mx) {
		mx = cnt[col[x]];
		sum = col[x];
	} else if (cnt[col[x]] == mx) {
		sum += col[x];
	}
	for (auto y : adj[x]) {
		if (y == fa || y == p) {
			continue;
		}
		self(self, y, x, val, p);
	}
}; 
auto dfs2 = [&] (auto self, int x, int fa, int op) -> void {
	for (auto y : adj[x]) {
		if (y == fa || y == son[x]) {
			continue;
		}
		self(self, y, x, 0);
	}
	if (son[x]) {
		self(self, son[x], x, 1);
	}
	calc(calc, x, fa, 1, son[x]);
	ans[x] = sum;
	if (op == 0) {
		calc(calc, x, fa, -1, 0);
		sum = mx = 0;
	}
};
dfs1(dfs1, 1, 0);
dfs2(dfs2, 1, 0, 0);