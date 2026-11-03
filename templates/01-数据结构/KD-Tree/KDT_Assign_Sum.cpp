// 依赖 KDT.cpp。
// 区域点权赋值，区域求和
struct Tag {
	int v;
	Tag() : v(-inf) {}
	Tag(int x) : v(x) {}
	void apply(const Tag& oth) {
		if (oth.v != -inf) {
			v = oth.v;
		}
	}
};
struct Info {
	int sum = 0;
	Info() : sum(0) {}
	Info(int x) : sum(x) {}
	Info operator+(const Info& oth) const {
		return Info(sum + oth.sum);
	}
	void apply(const Tag& tag, int sz) {
		if (tag.v != -inf) {
			sum = tag.v * sz;
		}
	}
};


