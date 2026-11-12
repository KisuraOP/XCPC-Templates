/*
插入、查询 O(B)，B 为位数；回滚 O(k)，k 为撤销的基向量数。

Node t(n);
n 为最高二进制位的下标。

t.insert(x);
插入 x。

int ans = t.getans();
获取最大异或和。

int v = t.ver.size();
记录当前状态。

t.roll(v);
回滚到记录的状态。
*/

struct Node {
	int n;
	vector<int> p, ver;
	Node(int _n) : n(_n), p(_n + 1) {}
	void insert(int x) {
		for (int i = n; i >= 0; i--) {
			if (!(x >> i)) {
				continue;
			}
			if (!p[i]) {
				p[i] = x;
				ver.push_back(i);
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
	void roll(int v) {
		while (ver.size() > v) {
			p[ver.back()] = 0;
			ver.pop_back();
		}
	}
};
