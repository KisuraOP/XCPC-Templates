/*
Node t(n);
其中 n 为插入的数在二进制下的最大位数。
注意: 如果 ai < 2^64, n 应当是 63 而不是 64。
尤其注意 long long 右移 64 位是未定义行为。

t.insert(x);
在线性基中插入 x。

int res = t.getans();
获取最大异或和。
*/
struct Node {
	int n;
	vector<int> p;
	Node(int _n) : n(_n), p(_n + 1) {}
	void insert(int x) {
		for (int i = n; i >= 0; i--) {
			if (!(x >> i)) {
				continue;
			}
			if (!p[i]) {
				p[i] = x;
				break;
			}
			x ^= p[i];
		}
	}
	int getans() {
		int res = 0;
		for (int i = n; i >= 0; i--) {
			if ((res ^ p[i]) > res) {
				res ^= p[i];
			}
		}
		return res;
	}
};