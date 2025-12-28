/*
时间复杂度 O(nm\log m)

Johnson G(adj);
adj 为邻接表。

vector<vector<int>> dis = G.work();
返回一个二维数组 dis，dis[x][y] 代表 x -> y 的最短路长度。
若图中存在负环，则 dis 中元素全为 -1。
若 x 和 y 不连通（不存在 x -> y 的路径），则 dis[x][y] = inf。
inf 需要宏定义。
*/

#define _node vector<vector<array<int, 2>>>
struct Johnson {
	int n;
	_node adj;
	vector<int> h, dis;
	Johnson(_node Adj) {
		adj = Adj;
		this->n = Adj.size() - 1;
		init();
	}
	void init() {
		h.resize(n + 1);
		dis.resize(n + 1);
		for (int i = 1; i <= n; i++) {
			adj[0].push_back({i, 0});
		}
	}
	bool spfa(int s) {
		vector<int> vis(n + 1), circle(n + 1);
		h.assign(n + 1, inf);
		queue<int> q;
		vis[s] = true;
		h[s] = 0;
		q.push(s);
		while(!q.empty()) {
			int x = q.front();
			q.pop();
			vis[x] = false;
			for(auto [y, w] : adj[x]) {
				if(h[y] > h[x] + w) {
					h[y] = h[x] + w;
					if(!vis[y]) {
						if(++circle[y] >= n + 1) {
							return false;
						}
						vis[y] = true;
						q.push(y);
					}
				}
			}
		}
		return true;	
	}
	void dijkstra(int s) {
		priority_queue<array<int, 2>> q;
		dis.assign(n + 1, inf);
		vector<int> vis(n + 1);
		dis[s] = 0;
		q.push({0, s});
		while(!q.empty()) {
			int x = q.top()[1];
			q.pop();
			if(vis[x]) {
				continue;
			}
			vis[x] = true;
			for(auto [y, w] : adj[x]) {
				if(dis[y] > dis[x] + w) {
					dis[y] = dis[x] + w;
					q.push({-dis[y], y});
				}
			}
		}
	}
	vector<vector<int>> work() {
		vector ans(n + 1, vector<int>(n + 1, -inf));
		if (!spfa(0)) {
			return ans;
		}
		for (int x = 1; x <= n; x++) {
			for (auto &[y, w] : adj[x]) {
				w += h[x] - h[y];
			}
		}
		for (int i = 1; i <= n; i++) {
			dijkstra(i);
			for (int j = 1; j <= n; j++) {
				if (dis[j] == inf) {
					ans[i][j] = inf; 
				} else {
					ans[i][j] = dis[j] + (h[j] - h[i]);
				}
			}
		}
		return ans;
	}
};