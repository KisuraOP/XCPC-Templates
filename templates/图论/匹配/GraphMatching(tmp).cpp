// 一般图最大匹配 O(nm^2)
// 返回 mat[i] 表示与点 i 匹配的点的编号。
// 若没有点与 i 匹配则 mat[i] = -1。
struct graphMatching {
	int n;
	vector<vector<int>> adj;
	vector<int> mat, aux, lab, rt, p;
	int tim;

	graphMatching(int n) : n(n), adj(n + 1), mat(n + 1, -1), 
	aux(n + 1, -1), lab(n + 1), rt(n + 1), p(n + 1, -1), tim(-1) {}
	void add(int x, int y) {
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	int lca(int x, int y) {
		tim++;
		while (true) {
			if (x != -1) {
				if (aux[x] == tim) {
					return x;
				}
				aux[x] = tim;
				if (mat[x] == -1) {
					x = -1;
				} else {
					x = rt[p[mat[x]]];
				}
			}
			swap(x, y);
		}
	}
	void augment(int x) {
		while (x != -1) {
			int px = p[x];
			int nx = mat[px];
			mat[x] = px;
			mat[px] = x;
			x = nx;
		}
	}
	void greedy() {
		mt19937_64 rng(time(0));
		vector<int> ord(n + 1);
		iota(ord.begin(), ord.end(), 0);
		shuffle(ord.begin(), ord.end(), rng);
		for (int i = 1; i <= n; i++) {
			int x = ord[i];
			if (mat[x] == -1) {
				for (auto y : adj[x]) {
					if (mat[y] == -1) {
						mat[x] = y;
						mat[y] = x;
						break;
					}
				}
			}
		}
	};
	vector<int> solve() {
		greedy();
		queue<int> q;
		auto blossom = [&] (int x, int y, int z) {
			while (rt[x] != z) {
				p[x] = y;
				y = mat[x];
				if (lab[y] == 1) {
					lab[y] = 0;
					q.push(y);
				}
				rt[x] = rt[y] = z;
				x = p[y];
			}
		};
		auto bfs = [&] (int S) {
			fill(lab.begin(), lab.end(), -1);
			iota(rt.begin(), rt.end(), 0);
			while (!q.empty()) {
				q.pop();
			}
			q.push(S);
			lab[S] = 0;
			while (!q.empty()) {
				int x = q.front();
				q.pop();
				for (auto y : adj[x]) {
					if (lab[y] == -1) {
						lab[y] = 1;
						p[y] = x;
						if (mat[y] == -1) {
							augment(y);
							return true;
						}
						lab[mat[y]] = 0;
						q.push(mat[y]);
						continue;
					} else if (lab[y] == 0 && rt[x] != rt[y]) {
						int z = lca(rt[x], rt[y]);
						blossom(y, x, z);
						blossom(x, y, z);
					}
				}
			}
			return false;
		};
		for (int i = 1; i <= n; i++) {
			if (mat[i] == -1) {
				bfs(i);
			}
		}
		return mat;
	}
};