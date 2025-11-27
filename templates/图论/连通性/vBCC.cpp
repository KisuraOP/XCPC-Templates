/*
VBCC G(n);

G.addEdge(x, y);
连一条 x -> y 的无向边。

G.work_Node();

其中：
邻接表 adj 第二维存储该条边的编号 eid。
scc[x] 存储编号为 x 的点双里的点的编号。
c[x] 存储编号为 x 的点所在的点双编号。
ebel[eid] 存储编号为 eid 的边所在的点双编号。
edges[eid] 存储编号为 eid 的边的两个端点。
iscut[x] = 0/1 存储编号为 x 的点是否是割点。
*/
struct vBCC {
	int n;
	vector<vector<array<int, 2>>> adj;
	vector<vector<int>> scc, c;
	vector<int> dfn, low;
	int tim, cnt;
	
	vector<array<int, 2>> edges;
	vector<int> ebel, estk;
	
	vector<int> mark;
	int flag;
	
	vector<int> iscut;
	
	vBCC(int _n) : n(_n), adj(n + 1), dfn(n + 1), 
	low(n + 1), c(n + 1), mark(n + 1), iscut(n + 1) {
		tim = cnt = 0;
		flag = 1;
		scc.push_back({});
		edges.push_back({0, 0});
		ebel.push_back(0);
	}
	
	void addEdge(int x, int y) {
		edges.push_back({x, y});
		ebel.push_back(0);
		int eid = edges.size() - 1;
		adj[x].push_back({y, eid});
		adj[y].push_back({x, eid});
	}
	
	void tarjan_Node(int x, int par) {
		dfn[x] = low[x] = ++tim;
		int son = 0;
		for (auto [y, eid] : adj[x]) {
			if (!dfn[y]) {
				son++;
				estk.push_back(eid);
				
				tarjan_Node(y, x);
				low[x] = min(low[x], low[y]);
				
				if (low[y] >= dfn[x]) {
					cnt++;
					scc.push_back({});
					
					while (!estk.empty()) {
						int e = estk.back();
						estk.pop_back();
						ebel[e] = cnt;
						
						auto [u, v] = edges[e];
						
						if (mark[u] != flag) {
							scc[cnt].push_back(u);
							c[u].push_back(cnt);
							mark[u] = flag;
						}
						if (mark[v] != flag) {
							scc[cnt].push_back(v);
							c[v].push_back(cnt);
							mark[v] = flag;
						}
						if (e == eid) {
							break;
						}
					}
					flag++;
				}
				if (par && low[y] >= dfn[x]) {
					iscut[x] = true;
				}
			} else if (y != par) {
				if (dfn[y] < dfn[x]) {
					estk.push_back(eid);
				}
				low[x] = min(low[x], dfn[y]);
			}
		}
		if (!par && son > 1) {
			iscut[x] = true;
		}
		if (par == 0 && son == 0) {
			cnt++;
			scc.push_back({x});
			c[x].push_back(cnt);
		}
	}
	void work_Node() {
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) {
				tarjan_Node(i, 0);
			}
		}
	}
};