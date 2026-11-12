/*
Node t(n);
n 为最高二进制位的下标，最低位的下标为 0。

bool ok = t.count(x);
判断能否从已插入的数中选出若干个，使异或和为 x。

int ways = t.getways(x);
返回异或和为 x 的选法数，对 modp 取模。
*/
int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % modp) {
		if (n & 1) {
			s = s * k % modp;
		}
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