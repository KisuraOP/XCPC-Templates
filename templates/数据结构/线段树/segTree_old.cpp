struct SegmentTree {
	int n;
	vector<int> sum;
	vector<int> mn;
	vector<int> mx;
	vector<int> Add;
	SegmentTree(int size) {
		n = size;
		sum.resize(4 * n + 5, 0);
		Add.resize(4 * n + 5, 0);
		mn.resize(4 * n + 5, inf);
		mx.resize(4 * n + 5, -inf);
	}

	#define mid ((l + r) >> 1)
	#define ls (p << 1)
	#define rs (p << 1 | 1)

	inline void pushup(int p) {
		sum[p] = sum[ls] + sum[rs];
		mn[p] = min(mn[ls], mn[rs]);
		mx[p] = max(mx[ls], mx[rs]);
	}
	inline void pushdown(int p, int l, int r) {
		if (Add[p]) {
			Add[ls] += Add[p];
			Add[rs] += Add[p];			
			sum[ls] += (mid - l + 1) * Add[p];
			sum[rs] += (r - mid) * Add[p];
			mn[ls] += Add[p];
			mn[rs] += Add[p];
			mx[ls] += Add[p];
			mx[rs] += Add[p];
			Add[p] = 0;
		}
	}
	void in_build(int p, int l, int r, vector<int> &nums) {
		if (l == r) {
			sum[p] = nums[l];
			mn[p] = nums[l];
			mx[p] = nums[l];
			return ;
		}
		in_build(ls, l, mid, nums);
		in_build(rs, mid + 1, r, nums);
		pushup(p);
	}
	void update_add(int p, int l, int r, int ql, int qr, int val) {
		if (ql <= l && qr >= r) {
			sum[p] += val * (r - l + 1);
			mn[p] += val;
			mx[p] += val;
			Add[p] += val;
			return ;
		}
		pushdown(p, l, r);
		if (ql <= mid) {
			update_add(ls, l, mid, ql, qr, val);
		}
		if (qr > mid) {
			update_add(rs, mid + 1, r, ql, qr, val);
		}
		pushup(p);
	}
	void update_change(int p, int l, int r, int ql, int qr, int val) {
        if (ql <= l && qr >= r) {
            sum[p] = val * (r - l + 1);
            mn[p] = val;
            mx[p] = val;
            Add[p] = val;
            return ;
        }
        pushdown(p, l, r);
        if (ql <= mid) {
        	update_change(ls, l, mid, ql, qr, val);
        }
        if (qr > mid) {
        	update_change(rs, mid + 1, r, ql, qr, val);
        }
        pushup(p);
    }
    int range_query_min(int p, int l, int r, int ql, int qr) {
		if (ql <= l && qr >= r) {
			return mn[p];
		}
		pushdown(p, l, r);
		int res = inf;
		if (ql <= mid) {
			res = min(res, range_query_min(ls, l, mid, ql, qr));
		}
		if (qr > mid) {
			res = min(res, range_query_min(rs, mid + 1, r, ql, qr));
		}
		return res;
	}
    int range_query_max(int p, int l, int r, int ql, int qr) {
		if (ql <= l && qr >= r) {
			return mx[p];
		}
		pushdown(p, l, r);
		int res = -inf;
		if (ql <= mid) {
			res = max(res, range_query_max(ls, l, mid, ql, qr));
		}
		if (qr > mid) {
			res = max(res, range_query_max(rs, mid + 1, r, ql, qr));
		}
		return res;
	}
	int range_query(int p, int l, int r, int ql, int qr) {
		if (ql <= l && qr >= r) {
			return sum[p];
		}
		pushdown(p, l, r);
		int res = 0;
		if (ql <= mid) {
			res += range_query(ls, l, mid, ql, qr);
		}
		if (qr > mid) {
			res += range_query(rs, mid + 1, r, ql, qr);
		}
		return res;
	}

	void build(vector<int> &nums) {
		in_build(1, 1, n, nums);
	}
	void add(int ql, int qr, int val) {
		update_add(1, 1, n, ql, qr, val);
	}
	void change(int ql, int qr, int val) {
        update_change(1, 1, n, ql, qr, val);
    }
	int query_min(int ql, int qr) {
		return range_query_min(1, 1, n, ql, qr);
	}
	int query_max(int ql, int qr) {
		return range_query_max(1, 1, n, ql, qr);
	}
	int query(int ql, int qr) {
		return range_query(1, 1, n, ql, qr);
	}
};