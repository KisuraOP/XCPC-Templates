/*
Node t(n);
n 为插入的数在二进制下的最大位数。

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