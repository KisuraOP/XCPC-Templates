// 依赖 KDT.cpp。
// mod 按题目设置。
// 区域点权乘法 + 加法，区域求和
struct Tag {
	int mul, add;
	Tag() : mul(1), add(0) {}
	Tag(int x, int y) : mul(x), add(y) {}
	void apply(const Tag& oth) {
		mul = (mul * oth.mul) % mod;
		add = (add * oth.mul + oth.add) % mod;
	}
};
struct Info {
	int sum = 0;
	Info() : sum(0) {}
	Info(int x) : sum(x % mod) {}
	Info operator+(const Info& oth) const {
		return Info((sum + oth.sum) % mod);
	}
	void apply(const Tag& tag, int sz) {
		sum = (sum * tag.mul % mod + tag.add * sz % mod) % mod;
	}
};


