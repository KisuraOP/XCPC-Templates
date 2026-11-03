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


