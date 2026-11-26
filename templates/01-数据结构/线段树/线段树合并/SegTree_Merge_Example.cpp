// 依赖 SegTree_Merge.cpp。
// 单点修改，区间最大值（记录下标）。
struct Tag {
	bool has_tag() const {
		return false;
	}
	void apply(const Tag &t) & {
	}
};
struct Info {
	int sum = 0, pos = 0;
	Info() {}
	Info(int x, int y) : sum(x), pos(y) {}
	void apply(const Tag &t) & {
	}
	void merge(const Info &oth) {
		sum += oth.sum;
		pos = oth.pos;
	}
};
Info operator+(const Info &a, const Info &b) {
	Info c;
	if (!a.pos) {
		return b;
	}
	if (!b.pos) {
		return a;
	}
	if (a.sum >= b.sum) {
		c.pos = a.pos;
		c.sum = a.sum;
	} else  {
		c.pos = b.pos;
		c.sum = b.sum;
	}
	return c;
}

// 依赖 SegTree_Merge.cpp。
// 区间加, 区间查
struct Tag {
	int add = 0;
	Tag() {}
	Tag(int A) : add(A) {}
	bool has_tag() const {
		return add != 0;
	}
	void apply(const Tag &t) & {
		add += t.add;
	}
};
struct Info {
	int sum = 0, len = 0;
	Info() {}
	Info(int x, int y = 1) : sum(x), len(y) {}
	void apply(const Tag &t) & {
		sum += t.add * len;
	}
	void merge(const Info &oth) {
		len = 1;
		sum += oth.sum;
	}
};
Info operator+(const Info &a, const Info &b) {
	Info c;
	c.sum = a.sum + b.sum;
	c.len = a.len + b.len;
	return c;
}

// 依赖 SegTree_Merge.cpp。
// 区间赋值, 区间查
struct Tag {
	int cov = 0;
	bool has_cov = false;
	Tag() {}
	Tag(int x) : cov(x), has_cov(true) {}
	bool has_tag() const {
		return has_cov;
	}
	void apply(const Tag &t) & {
		if (t.has_cov) {
			cov = t.cov;
			has_cov = true;
		}
	}
};
struct Info {
	int sum = 0, len = 0;
	Info() {}
	Info(int x, int y = 1) : sum(x), len(y) {}
	void apply(const Tag &t) & {
		if (t.has_cov) {
			sum = t.cov * len;
		}
	}
	void merge(const Info &oth) {
		len = 1;
		sum = oth.sum;
	}
};
Info operator+(const Info &a, const Info &b) {
	Info c;
	c.sum = a.sum + b.sum;
	c.len = a.len + b.len;
	return c;
}

// 依赖 SegTree_Merge.cpp。
// 区间乘 + 加
struct Tag {
	int mul = 1, add = 0;
	Tag() {}
	Tag(int x, int y) : mul(x), add(y) {}
	bool has_tag() const {
		return mul != 1 || add != 0;
	}
	void apply(const Tag &t) & {
		add *= t.mul;
		mul *= t.mul;
		add += t.add;
	}
};
struct Info {
	int sum = 0, len = 0;
	Info() {}
	Info(int x, int y = 1) : sum(x), len(y) {}
	void apply(const Tag &t) & {
		sum *= t.mul;
		sum += t.add * len;
	}
	void merge(const Info &oth) {
		len = 1;
		sum += oth.sum;
	}
};
Info operator+(const Info &a, const Info &b) {
	Info c;
	c.sum = a.sum + b.sum;
	c.len = a.len + b.len;
	return c;
}




