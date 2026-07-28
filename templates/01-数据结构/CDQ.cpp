struct Fenwick {
	int n;
	vector<int> t;
	Fenwick(int n) : n(n), t(n + 1) {}
	void add(int i, int x) {
		for ( ; i <= n; i += i & -i) {
			t[i] += x; 
		}
	}
	int sum(int i) {
		int res = 0;
		for ( ; i; i -= i & -i) {
			res += t[i];
		}
		return res;
	} 
};

struct Node {
	int a, b, c, id;
	bool friend operator < (const Node &x, const Node &y) {
		if (x.a != y.a) {
			return x.a < y.a;
		}
		if (x.b != y.b) {
			return x.b < y.b;
		}
		return x.c < y.c;
	}
};

// All 1-index
// 返回 res[i] 表示满足 aj <= ai && bj <= bi && cj <= ci 的 j 的数量
vector<int> solve(vector<int> &a, vector<int> &b, vector<int> &c) {
	int n = a.size() - 1;
	vector<Node> v(n + 1);
	vector<int> d;
	for (int i = 1; i <= n; i++) {
		v[i] = {a[i], b[i], c[i], i};
		d.push_back(c[i]);
	} 
	sort(d.begin(), d.end());
	d.erase(unique(d.begin(), d.end()), d.end());
	for (int i = 1; i <= n; i++) {
		v[i].c = lower_bound(d.begin(), d.end(), v[i].c) - d.begin() + 1;
	}
	sort(v.begin() + 1, v.end());
	vector<Node> ord = v;

	Fenwick fen(d.size());
	vector<int> res(n + 1);
	vector<Node> t(n + 1);

	auto cdq = [&] (auto self, int l, int r) -> void {
		if (l >= r) {
			return ;
		}
		int mid = l + r >> 1;
		self(self, l, mid);
		self(self, mid + 1, r);

		int i = l, j = mid + 1, k = l;

		while (j <= r) {
			while (i <= mid && v[i].b <= v[j].b) {
				fen.add(v[i].c, 1);
				t[k++] = v[i++];
			}
			res[v[j].id] += fen.sum(v[j].c);
			t[k++] = v[j++];
		}
		for (int p = l; p < i; p++) {
			fen.add(v[p].c, -1);
		}
		while (i <= mid) {
			t[k++] = v[i++];
		}
		for (int p = l; p <= r; p++) {
			v[p] = t[p];
		}
	};

	cdq(cdq, 1, n);

	// 处理完全相同三元组
	for (int l = 1; l <= n; ) {
		int r = l, mx = 0;
		while (r <= n && ord[r].a == ord[l].a && ord[r].b == ord[l].b && ord[r].c == ord[l].c) {
			mx = max(mx, res[ord[r].id]);
			r++;
		}
		for (int p = l; p < r; p++) {
			res[ord[p].id] = mx;
		}
		l = r;
	}
	return res;
}