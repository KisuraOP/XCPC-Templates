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
