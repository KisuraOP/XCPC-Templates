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


