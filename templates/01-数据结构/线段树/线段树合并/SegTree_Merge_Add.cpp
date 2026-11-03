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


