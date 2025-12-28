/*
Node t;

bool ok = t.count(x);
判断 x 是否能被插入线性基中的数表示出来。

int ways = t.getways(x);
返回能表示出 x 的方案数量.
*/
int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % modp) {
		if (n & 1) s = s * k % modp;
	}
	return s;
}

struct Node {
	int n, tot, all;
	vector<int> p;
	Node(int _n) : n(_n), tot(0), all(0), p(_n + 1) {}
	void insert(int x) {
		all++;
		for (int i = n; i >= 0; i--) {
			if (!(x >> i)) {
				continue;
			}
			if (!p[i]) {
				p[i] = x;
				tot++;
				break;
			}
			x ^= p[i];
		}
	}
	int count(int x) {
		for (int i = n; i >= 0; i--) {
			if (x >> i & 1) {
				x ^= p[i];
			}
		}
		return x == 0;
	}
	int getways(int x) {
		if (!count(x)) {
			return 0;
		}
		return qpow(2, all - tot);
	}
};