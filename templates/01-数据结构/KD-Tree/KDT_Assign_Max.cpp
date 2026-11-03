// 依赖 KDT.cpp。
// 区域点权赋值，区域求最大值
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
	int mx;
	Info() : mx(-inf) {} 
	Info(int x) : mx(x) {}
	Info operator+(const Info& oth) const {
		Info res;
		res.mx = max(mx, oth.mx);
		return res;
	}
	void apply(const Tag& tag, int sz) {
		if (tag.v != -inf) {
			mx = tag.v;
		}
	}
};


