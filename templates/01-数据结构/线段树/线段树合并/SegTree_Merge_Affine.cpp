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
