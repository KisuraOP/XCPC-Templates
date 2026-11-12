// 时间复杂度: 插入摊还 O(log^2 n), 修改、查询 O(log^2 n + n^{1 - 1 / k})

template <class Info, typename T = int>
struct Pt {
	array<T, 3> x;
	Info v;
};

template <class Info, class Tag, typename T = int>
struct KDT {
	using Pt = Pt<Info, T>;
	struct Node {
		int l = 0, r = 0, sz = 0, has_tag = 0;
		array<T, 3> mn, mx;
		Pt p;
		Info sum;
		Tag tag;
	};

	int K;
	vector<Node> tr;
	vector<Pt> buf;
	vector<int> bin;
	int rt[35];

	KDT(int k) : K(k) {
		tr.push_back({});
		memset(rt, 0, sizeof(rt));
	}
	int new_node(Pt& pt) {
		int u;
		if (!bin.empty()) {
			u = bin.back();
			bin.pop_back();
		} else {
			u = tr.size();
			tr.push_back({});
		}
		tr[u].l = tr[u].r = tr[u].has_tag = 0;
		tr[u].p = pt;
		tr[u].tag = Tag();
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
				tr[u].sum = tr[u].sum + tr[v].sum;
				for (int i = 0; i < K; i++) {
					tr[u].mn[i] = min(tr[u].mn[i], tr[v].mn[i]);
					tr[u].mx[i] = max(tr[u].mx[i], tr[v].mx[i]);
				}
			}
		}
	}
	void apply(int u, const Tag& v) {
		if (u) {
			tr[u].sum.apply(v, tr[u].sz);
			tr[u].p.v.apply(v, 1);
			tr[u].tag.apply(v);
			tr[u].has_tag = 1;
		}
	}
	void down(int u) {
		if (tr[u].has_tag) {
			apply(tr[u].l, tr[u].tag);
			apply(tr[u].r, tr[u].tag);
			tr[u].tag = Tag();
			tr[u].has_tag = 0;
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
	void add(int u, Pt& A, Pt& B, const Tag& v) {
		if (!u || out(u, A, B)) {
			return ;
		}
		if (in(u, A, B)) {
			return apply(u, v);
		}
		down(u);
		if (pt_in(tr[u].p, A, B)) {
			tr[u].p.v.apply(v, 1);
		}
		add(tr[u].l, A, B, v);
		add(tr[u].r, A, B, v);
		up(u);
	}
	Info ask(int u, Pt& A, Pt& B) {
		if (!u || out(u, A, B)) {
			return Info();
		}
		if (in(u, A, B)) {
			return tr[u].sum;
		}
		down(u);
		Info res;
		if (pt_in(tr[u].p, A, B)) {
			res = res + tr[u].p.v;
		}
		res = res + ask(tr[u].l, A, B);
		res = res + ask(tr[u].r, A, B);
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
	void add_all(Pt& A, Pt& B, const Tag& v) { // 区域改
		for (int i = 0; i < 35; i++) {
			if (rt[i]) {
				add(rt[i], A, B, v);
			}
		}
	}
	Info ask_all(Pt& A, Pt& B) { // 区域查
		Info res;
		for (int i = 0; i < 35; i++) {
			if (rt[i]) {
				res = res + ask(rt[i], A, B);
			}
		}
		return res;
	}
};


