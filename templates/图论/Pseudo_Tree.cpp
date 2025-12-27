struct PseudoTree {
	int n, tim;
	vector<int> vis; // used to un-connected graph
	vector<int> faP, faW, ins; // used to find cir
	vector<long long> cir, dCir;  // used to store circle and dis-between
	vector<long long> inCir, dep, mx; // used to dfs subtree
	vector<vector<array<int, 3>>> adj;
	PseudoTree(int n) : n(n), tim(0), vis(n + 1), faP(n + 1), faW(n + 1), 
	ins(n + 1), inCir(n + 1), dep(n + 1), mx(n + 1), adj(n + 1) {}
	void addEdge(int x, int y, int w) {
		adj[x].push_back({y, w, ++tim});
		adj[y].push_back({x, w, tim});
	}
	void findCir(int x, int fa, int from) {
		vis[x] = true;
		ins[x] = true;
		faP[x] = fa;
		for (auto [y, w, id] : adj[x]) {
			if (from == id) {
				continue;
			}
			faW[y] = w;
			if (ins[y]) {
				if (cir.empty()) {
					cir.push_back(y);
					dCir.push_back(faW[y]);
					for (int i = x; i != y; i = faP[i]) {
						cir.push_back(i);
						dCir.push_back(faW[i]);
					}
				}
			}
			if (vis[y]) {
				continue;
			}
			findCir(y, x, id);
		}
		ins[x] = false;
	}
	void get_circle(int x) {
		cir.clear();
		dCir.clear();
		findCir(x, 0, -1);
	}
	long long getSubtreeDia(int rt) {
		long long mxVal = 0, mxNode = 0;
		auto dfs = [&] (auto self, int x, int fa) -> void {
			for (auto [y, w, _] : adj[x]) {
				if (y == fa || inCir[y]) {
					continue;
				}
				dep[y] = dep[x] + w;
				if (dep[y] > mxVal) {
					mxVal = dep[y];
					mxNode = y;
				}
				self(self, y, x);
			}
		};
		dfs(dfs, rt, 0);
		dep[mxNode] = 0;
		mxVal = 0;
		dfs(dfs, mxNode, 0);
		return mxVal;
	}
	long long scanSubtree() {
		long long res = 0;
		for (auto x : cir) {
			inCir[x] = false;
			res = max(res, getSubtreeDia(x));
			inCir[x] = true;
		}
		return res;
	}
	void getMxDep(int x, int fa) {
		mx[x] = 0;
		for (auto [y, w, _] : adj[x]) {
			if (y == fa || inCir[y]) {
				continue;
			}
			getMxDep(y, x);
			mx[x] = max(mx[x], mx[y] + w);
		}
	}
	long long scan_circle() {
		vector<long long> val;
		for (auto x : cir) {
			getMxDep(x, 0);
			val.push_back(mx[x]);
		}
		
		int len = cir.size();
		cir.insert(cir.end(), cir.begin(), cir.end());
		rotate(dCir.rbegin(), dCir.rbegin() + 1, dCir.rend());
		dCir.insert(dCir.end(), dCir.begin(), dCir.end());
		val.insert(val.end(), val.begin(), val.end());

		for (int i = 1; i < dCir.size(); i++) {
			dCir[i] += dCir[i - 1];
		}
		long long res = 0;
		deque<int> q;
		for (int i = 0; i < cir.size(); i++) {
			while (!q.empty() && i - q.front() >= len) {
				q.pop_front();
			}
			if (!q.empty()) {
				res = max(res, val[i] + val[q.front()] + dCir[i] - dCir[q.front()]);
			}
			while (!q.empty() && val[q.back()] - dCir[q.back()] <= val[i] - dCir[i]) {
				q.pop_back();
			}
			q.push_back(i);
		}
		return res;
	}
	long long get_diameter() {
		long long res = 0;
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				get_circle(i);
				for (auto x : cir) {
					inCir[x] = true;
				}
				res += max(scanSubtree(), scan_circle());
			}
		}
		return res;
	}
};