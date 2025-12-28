/*
一般来说，有着如下步骤：

- 遍历每一个节点。
- 先递归所有轻儿子，递归后消除贡献。
- 然后递归重儿子，不消除贡献。
- 更新答案。

例题：给定一棵树，对每个节点求其子树中出现次数最多的颜色的编号和。
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