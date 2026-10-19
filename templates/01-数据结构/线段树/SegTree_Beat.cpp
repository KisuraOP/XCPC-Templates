// 时间复杂度：O(n\log^2 n)。
struct Node {
	vector<int> sum, mx, mn, sx, sn, cx, cn;
	vector<int> tc, ta, L, R;
	#define N 4 * n + 5
	Node(int n) : sum(N), mx(N), mn(N), sx(N), sn(N), cx(N), cn(N), tc(N), ta(N), L(N), R(N) {} 

	#define ls (p << 1)
	#define rs (p << 1 | 1)
	#define mid (L[p] + R[p] >> 1)

	void pushup(int p) {
		sum[p] = sum[ls] + sum[rs];
		mx[p] = max(mx[ls], mx[rs]);
		mn[p] = min(mn[ls], mn[rs]);
		sx[p] = max(mx[ls] == mx[p] ? sx[ls] : mx[ls], mx[rs] == mx[p] ? sx[rs] : mx[rs]);
		sn[p] = min(mn[ls] == mn[p] ? sn[ls] : mn[ls], mn[rs] == mn[p] ? sn[rs] : mn[rs]);
		cx[p] = (mx[ls] == mx[p] ? cx[ls] : 0) + (mx[rs] == mx[p] ? cx[rs] : 0);
		cn[p] = (mn[ls] == mn[p] ? cn[ls] : 0) + (mn[rs] == mn[p] ? cn[rs] : 0);
	}
	void Cover(int p, int w) {
		sum[p] = (R[p] - L[p] + 1) * w;
		mx[p] = mn[p] = tc[p] = w;
		sx[p] = -inf;
		sn[p] = inf;
		cx[p] = cn[p] = R[p] - L[p] + 1;
		ta[p] = 0;
	}
	void Add(int p, int w) {
		sum[p] += (R[p] - L[p] + 1) * w;
		if (cx[p] < R[p] - L[p] + 1) sx[p] += w;
		if (cn[p] < R[p] - L[p] + 1) sn[p] += w;
		mx[p] += w;
		mn[p] += w;
		ta[p] += w;
	} 
	void Chmin(int p, int w) {
		if (mx[p] == mn[p]) return Cover(p, w);
		sum[p] += (w - mx[p]) * cx[p];
		if (sn[p] == mx[p]) sn[p] = w;
		mx[p] = w;
	}
	void Chmax(int p, int w) {
		if (mx[p] == mn[p]) return Cover(p, w);
		sum[p] += (w - mn[p]) * cn[p];
		if (sx[p] == mn[p]) sx[p] = w;
		mn[p] = w;
	}
	void pushdown(int p) {
		if (tc[p] != inf) {
			Cover(ls, tc[p]);
			Cover(rs, tc[p]);
			tc[p] = inf;
		}
		if (ta[p]) {
			Add(ls, ta[p]);
			Add(rs, ta[p]);			
			ta[p] = 0;
		}
		for (int x : {ls, rs}) {
			if (mx[x] > mx[p]) Chmin(x, mx[p]);
			if (mn[x] < mn[p]) Chmax(x, mn[p]);
		}
	}
	void build(int p, int l, int r, vector<int> &a) {
		L[p] = l;
		R[p] = r;
		tc[p] = inf;
		ta[p] = 0;
		if (l == r) {
			sum[p] = mx[p] = mn[p] = a[l];
			sx[p] = -inf;
			sn[p] = inf;
			cx[p] = cn[p] = 1;
			return ;
		}
		build(ls, l, mid, a);
		build(rs, mid + 1, r, a);
		pushup(p);
	}
	int get_sum(int p, int l, int r) {
		if (l <= L[p] && r >= R[p]) {
			return sum[p];
		}
		pushdown(p);	
		int res = 0;
		if (l <= mid) {
			res += get_sum(ls, l, r);
		}
		if (r > mid) {
			res += get_sum(rs, l, r);
		}
		return res;
	}
	int get_max(int p, int l, int r) {
		if (l <= L[p] && r >= R[p]) {
			return mx[p];
		}
		pushdown(p);
		int res = -inf;
		if (l <= mid) {
			res = max(res, get_max(ls, l, r));
		}
		if (r > mid) {
			res = max(res, get_max(rs, l, r));
		}
		return res;
	}
	int get_min(int p, int l, int r) {
		if (l <= L[p] && r >= R[p]) {
			return mn[p];
		}
		pushdown(p);
		int res = inf;
		if (l <= mid) {
			res = min(res, get_min(ls, l, r));
		}
		if (r > mid) {
			res = min(res, get_min(rs, l, r));
		}
		return res;
	}
	void modofy_Add(int p, int l, int r, int w) {
		if (l <= L[p] && r >= R[p]) {
			return Add(p, w);
		}
		pushdown(p);
		if (l <= mid) {
			modofy_Add(ls, l, r, w);
		}
		if (r > mid) {
			modofy_Add(rs, l, r, w);
		}
		pushup(p);
	}
	void modify_max(int p, int l, int r, int w) {
		if (mn[p] >= w) {
			return ;
		}
		if (l <= L[p] && r >= R[p] && mx[p] <= w) {
			return Cover(p, w);
		}
		if (l <= L[p] && r >= R[p] && sn[p] > w) {
			return Chmax(p, w);
		}
		pushdown(p);
		if (l <= mid) {
			modify_max(ls, l, r, w);
		}
		if (r > mid) {
			modify_max(rs, l, r, w);
		}
		pushup(p);
	}
	void modify_min(int p, int l, int r, int w) {
		if (mx[p] <= w) {
			return ;
		}
		if (l <= L[p] && r >= R[p] && mn[p] >= w) {
			return Cover(p, w);
		}
		if (l <= L[p] && r >= R[p] && sx[p] < w) {
			return Chmin(p, w);
		}
		pushdown(p);
		if (l <= mid) {
			modify_min(ls, l, r, w);
		}
		if (r > mid) {
			modify_min(rs, l, r, w);
		}
		pushup(p);
	}
	#undef N
	#undef ls
	#undef rs
	#undef mid
};