/*
区间最大异或和，支持末尾追加。B 为位数。
预处理 O(nB)，追加、查询 O(B)。

Basis t(n);
n 为序列的最大长度。

t.add(x);
在末尾追加 x。

int ans = t.query(l, r);
查询区间 [l,r] 的最大异或和。
*/

constexpr int B = 22;
struct Basis {
	int n = 0;
	vector<array<int, B>> p, pos;
	Basis(int m) : p(m + 1), pos(m + 1) {}
	void add(int x) {
		int r = ++n, t = r;
		p[r] = p[r - 1];
		pos[r] = pos[r - 1];
		for (int i = B - 1; i >= 0; i--) {
			if (!(x >> i & 1)) {
				continue;
			}
			if (!p[r][i]) {
				p[r][i] = x;
				pos[r][i] = t;
				break;
			}
			if (pos[r][i] < t) {
				swap(pos[r][i], t);
				swap(p[r][i], x);
			}
			x ^= p[r][i];
		}
	}
	int query(int l, int r) const {
		int ans = 0;
		for (int i = B - 1; i >= 0; i--) {
			if (pos[r][i] >= l) {
				ans = max(ans, ans ^ p[r][i]);
			}
		}
		return ans;
	}
};

void solve() {
	int n, Q;
	cin >> n >> Q;
	Basis t(n);
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		t.add(x);
	}
	while (Q--) {
		int l, r;
		cin >> l >> r;
		cout << t.query(l, r) << "\n";
	}
}
