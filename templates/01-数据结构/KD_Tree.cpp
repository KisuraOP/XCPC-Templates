// 时间复杂度: 插入 O(log^2 n), 修改 O(n^{1 - 1 / k}), 查询 O(n^{1 - 1 / k})
// 空间复杂度: 严格 O(n)
struct Pt {
	int x[3], v;
};
struct Node {
	int l, r, sz, sum, tag, mn[3], mx[3];
	Pt p;
};
struct KDT {
	int K;
	vector<Node> tr;
	vector<Pt> buf;
	vector<int> bin;
	int rt[35];
	KDT(int k) : K(k) {
		tr.push_back({});
		memset(rt, 0, sizeof(rt));
	}
	int new_node(const Pt& pt) {
		int u;
		if (!bin.empty()) {
			u = bin.back();
			bin.pop_back();
		} else {
			u = tr.size();
			tr.push_back({});
		}
		tr[u].l = tr[u].r = tr[u].tag = 0;
		tr[u].p = pt;
		up(u);
		return u;
	}
	void up(int u) {
		tr[u].sz = 1;
		tr[u].sum = tr[u].p.v;
		for (int i = 0; i < K; i++) {
			tr[u].mn[i] = tr[u].mx[i] = tr[u].p.x[i];
		}
		for (int v : {tr[u].l, tr[u].r}) {
			if (v) {
				tr[u].sz += tr[v].sz;
				tr[u].sum += tr[v].sum;
				for (int i = 0; i < K; i++) {
					tr[u].mn[i] = min(tr[u].mn[i], tr[v].mn[i]);
					tr[u].mx[i] = max(tr[u].mx[i], tr[v].mx[i]);
				}
			}
		}
	}
	void apply(int u, int v) {
		if (u) {
			tr[u].sum += tr[u].sz * v;
			tr[u].p.v += v;
			tr[u].tag += v;
		}
	}
	void down(int u) {
		if (tr[u].tag) {
			apply(tr[u].l, tr[u].tag);
			apply(tr[u].r, tr[u].tag);
			tr[u].tag = 0;
		}
	}
	bool out(int u, Pt& A, Pt& B) {
		for (int i = 0; i < K; i++) {
			if (tr[u].mn[i] > B.x[i] || tr[u].mx[i] < A.x[i]) {
				return true;
			}
		}
		return false;
	}
	bool in(int u, Pt& A, Pt& B) {
		for (int i = 0; i < K; i++) {
			if (tr[u].mn[i] < A.x[i] || tr[u].mx[i] > B.x[i]) {
				return false;
			}
		}
		return true;
	}
	bool pt_in(Pt& p, Pt& A, Pt& B) {
		for (int i = 0; i < K; i++) {
			if (p.x[i] < A.x[i] || p.x[i] > B.x[i]) {
				return false;
			}
		}
		return true;
	}
	void add(int u, Pt& A, Pt& B, int v) {
		if (!u || out(u, A, B)) {
			return ;
		}
		if (in(u, A, B)) {
			return apply(u, v);
		}
		down(u);
		if (pt_in(tr[u].p, A, B)) {
			tr[u].p.v += v;
		}
		add(tr[u].l, A, B, v);
		add(tr[u].r, A, B, v);
		up(u);
	}
	int ask(int u, Pt& A, Pt& B) {
		if (!u || out(u, A, B)) {
			return 0ll;
		}
		if (in(u, A, B)) {
			return tr[u].sum;
		}
		down(u);
		int res = 0;
		if (pt_in(tr[u].p, A, B)) {
			res += tr[u].p.v;
		}
		res += ask(tr[u].l, A, B) + ask(tr[u].r, A, B);
		return res;
	}
	void flatten(int u) {
		if (u) {
			down(u);
			flatten(tr[u].l);
			buf.push_back(tr[u].p);
			flatten(tr[u].r);
			bin.push_back(u);
		}
	}
	int build(int L, int R, int d) {
		if (L > R) {
			return 0ll;
		}
		int mid = L + R >> 1;
		nth_element(buf.begin() + L, buf.begin() + mid, buf.begin() + R + 1, 
			[&](Pt& a, Pt& b) {
				return a.x[d] < b.x[d];
			});
		int u = new_node(buf[mid]);
		tr[u].l = build(L, mid - 1, (d + 1) % K);
		tr[u].r = build(mid + 1, R, (d + 1) % K);
		up(u);
		return u;
	}

	// ---------- 分割线 ----------

	void insert(Pt& pt) { // 插入一个坐标是 pt.x, 权值是 pt.v 的点
		buf.clear();
		buf.push_back(pt);
		for (int i = 0; i < 35; i++) {
			if (!rt[i]) {
				rt[i] = build(0, buf.size() - 1, 0);
				break;
			}
			flatten(rt[i]);
			rt[i] = 0;
		}
	}
	void add_all(Pt& A, Pt& B, int v) { // 给矩形/长方体区域内的点的点权 +v
		for (int i = 0; i < 35; i++) {
			if (rt[i]) {
				add(rt[i], A, B, v);
			}
		}
	}
	int ask_all(Pt& A, Pt& B) { // 求矩形/长方体区域内点的权值和
		int res = 0;
		for (int i = 0; i < 35; i++) {
			if (rt[i]) {
				res += ask(rt[i], A, B);
			}
		}
		return res;
	}
};