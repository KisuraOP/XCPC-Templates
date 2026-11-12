/*
RMQ_LCA.cpp 的扩展版。

int z = jump(x, k);
返回 x 的 k 级祖先，若不存在则返回 -1，O(log n)。
O(1) 查询版本见树论章节的 Level_Ancestor.cpp。

is_ancestor(x, y);
判断 x 是否是 y 的祖先。

int v = neighbor(x, y);
返回 x 到 y 路径上紧邻 x 的下一个点。
*/
using P = array<int, 2>;
struct rmqLCA {
	int n, tim;
	vector<int> dfn, dis, dep, tin, tout;
	vector<int> up[21];
	vector<P> st[21];
	rmqLCA(vector<vector<P>> &adj, int rt = 1): n(adj.size() - 1), 
	dfn(n + 1), dis(n + 1), dep(n + 1), tin(n + 1), tout(n + 1), tim(0) {
		for (int i = 0; i < 21; i++) {
			up[i].assign(n + 1, 0);
		}
		auto dfs = [&](auto self, int x, int f, int d, int w) -> void {
			dfn[x] = st[0].size();
			tin[x] = ++tim;
			dis[x] = w;
			dep[x] = d;
			up[0][x] = f;
			st[0].push_back({d, x});
			for (auto [y, wt] : adj[x]) {
				if (y != f) {
					self(self, y, x, d + 1, w + wt);
					st[0].push_back({d, x});
				}
			}
			tout[x] = tim;
		};
		dfs(dfs, rt, 0, 0, 0);
		int sz = st[0].size();
		for (int i = 1; (1 << i) <= sz; i++) {
			st[i].resize(sz - (1 << i) + 1);
			for (int j = 0; j + (1 << i) <= sz; j++) {
				st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
		for (int i = 1; i < 21; i++) {
			for (int j = 1; j <= n; j++) {
				if (up[i - 1][j] != 0) {
					up[i][j] = up[i - 1][up[i - 1][j]];
				}
			}
		}
	}
	int LCA(int x, int y) {
		int l = dfn[x], r = dfn[y];
		if (l > r) {
			swap(l, r);
		}
		int k = __lg(r - l + 1);
		return min(st[k][l], st[k][r - (1 << k) + 1])[1];
	}
	int dist(int x, int y) {
		return dis[x] + dis[y] - 2 * dis[LCA(x, y)];
	}
	int jump(int x, int k) {
		if (k < 0 || k > dep[x]) {
			return -1;
		}
		for (int i = 20; i >= 0; i--) {
			if (k >> i & 1) {
				x = up[i][x];
			}
		}
		return x == 0 ? -1 : x;
	}
	bool is_ancestor(int x, int y) {
		return tin[x] <= tin[y] && tout[x] >= tout[y];
	}
	int neighbor(int x, int v) {
		return is_ancestor(x, v) ? jump(v, dep[v] - dep[x] - 1) : up[0][x];
	}
};
