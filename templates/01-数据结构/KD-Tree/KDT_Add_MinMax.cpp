// 依赖 KDT.cpp。
// 区域点权加，区域求最大最小值
struct Tag {
	int add = 0;
	Tag() : add(0) {}
	Tag(int x) : add(x) {}
	void apply(const Tag& oth) {
		add += oth.add;
	}
};
struct Info {
	int mx, mn;
	Info() : mx(-inf), mn(inf) {} 
	Info(int x) : mx(x), mn(x) {}
	Info operator+(const Info& oth) const {
		Info res;
		res.mx = max(mx, oth.mx);
		res.mn = min(mn, oth.mn);
		return res;
	}
	void apply(const Tag& tag, int sz) {
		if (mx != -inf) {
			mx += tag.add;
		}
		if (mn != inf) {
			mn += tag.add;
		}
	}
};


