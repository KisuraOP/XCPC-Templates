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

// 依赖 KDT.cpp。
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

// 依赖 KDT.cpp。
// 区域按位异或，区域求和
struct Tag {
	int v = 0;
	Tag() : v(0) {}
	Tag(int x) : v(x) {}
	void apply(const Tag& oth) {
		v ^= oth.v;
	}
};
struct Info {
	int cnt[64]; // 维护每一位上 1 的个数
	Info() {
		memset(cnt, 0, sizeof(cnt));
	}
	Info(int x) {
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < 64; i++) {
			if ((x >> i) & 1) {
				cnt[i] = 1;
			}
		}
	}
	Info operator+(const Info& oth) const {
		Info res;
		for (int i = 0; i < 64; i++) {
			res.cnt[i] = cnt[i] + oth.cnt[i];
		}
		return res;
	}
	void apply(const Tag& tag, int sz) {
		for (int i = 0; i < 64; i++) {
			if ((tag.v >> i) & 1) {
				cnt[i] = sz - cnt[i];
			}
		}
	}
	int get_sum() const {
		int sum = -cnt[63];
		for (int i = 62; i >= 0; i--) {
			sum = (sum + cnt[i] / 2) * 2 + cnt[i] % 2;
		}
		return sum;
	}
};