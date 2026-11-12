/*
区间最大异或和，支持单点赋值。B 为位数。
建树 O(nB log B)，修改、查询 O(B^2 log n)。

build(1, 1, n, a);
用 a 建树。

modify(1, 1, n, x, v);
将 a[x] 改为 v。

Node res = query(1, 1, n, l, r);
返回区间 [l,r] 的线性基，求最大异或和的示例见 solve。
*/

constexpr int B = 22;
constexpr int N = 1e5 + 10;

struct Node {
	int p[B] {};
	void add(int x) {
		for (int i = B - 1; i >= 0; i--) {
			if (!(x >> i & 1)) {
				continue;
			}
			if (!p[i]) {
				p[i] = x;
				break;
			}
			x ^= p[i];
		}
	}
	Node operator+(const Node &a) const {
		Node res = a;
		for (int i = B - 1; i >= 0; i--) {
			if (p[i]) {
				res.add(p[i]);
			}
		}
		return res;
	}
} tr[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid (l + r >> 1)

void pushup(int p) {
	tr[p] = tr[ls] + tr[rs];
}
void build(int p, int l, int r, vector<int> &a) {
	if (l == r) {
		tr[p] = Node();
		tr[p].add(a[l]);
		return ;
	}
	build(ls, l, mid, a);
	build(rs, mid + 1, r, a);
	pushup(p);
}
void modify(int p, int l, int r, int x, int v) {
	if (l == r) {
		tr[p] = Node();
		tr[p].add(v);
		return ;
	}
	if (x <= mid) {
		modify(ls, l, mid, x, v);
	} else {
		modify(rs, mid + 1, r, x, v);
	}
	pushup(p);
}
Node query(int p, int l, int r, int ql, int qr) {
	if (ql <= l && qr >= r) {
		return tr[p];
	}
	Node res;
	if (ql <= mid) {
		res = res + query(ls, l, mid, ql, qr);
	}
	if (qr > mid) {
		res = res + query(rs, mid + 1, r, ql, qr);
	}
	return res;
}

#undef ls
#undef rs

void solve() {
	int n, Q;
	cin >> n >> Q;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	build(1, 1, n, a);
	while (Q--) {
		int l, r;
		cin >> l >> r;
		Node res = query(1, 1, n, l, r);
		int ans = 0;
		for (int i = B - 1; i >= 0; i--) {
			if ((ans ^ res.p[i]) > ans) {
				ans ^= res.p[i];
			}
		}
		cout << ans << "\n";
	}
}
