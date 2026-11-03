// 依赖 KDT.cpp。
// 区域点权加，区域点权和
struct Tag {
	int add = 0;
	Tag() : add(0) {} 
	Tag(int x) : add(x) {}
	void apply(const Tag& oth) {
		add += oth.add;
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
		sum += tag.add * sz;
	}
};


