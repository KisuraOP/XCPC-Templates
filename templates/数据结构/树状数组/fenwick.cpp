/*
Fenwick fen(n);
创建。

fen.add(x, v);
单点 x 的值 +v。

int res = fen.sum(x);
求区间 [1, x] 的和。

int res = fen.sum(l, r);
求区间 [l, r] 的和。

int res = fen.kth(x);
求全局第 x 小的数，此时为值域树状数组。
*/

struct Fenwick {
	int n;
	vector<int> tr;
	Fenwick(int n) { 
		this->n = n;
		tr.assign(n + 1, 0);
	}
	void add(int pos, int x) {
		for (int i = pos; i <= n; i += i & -i) {
			tr[i] += x;
		}
	}
	int sum(int pos) {
		int res = 0;
		for (int i = pos; i > 0; i -= i & -i) {
			res += tr[i];
		}
		return res;
	}
	int query(int l, int r) {
		return sum(r) - sum(l - 1);
	}
	int kth(int k) {
		// tr[x] count the cnt of x
		int res = 0, cnt = 0;
		for (int i = 20; i >= 0; i--) {
			res += (1LL << i);
			if (res > n || cnt + tr[res] >= k) {
				res -= (1LL << i);
			} else {
				cnt += tr[res];
			}
		}
		return res + 1;
	}
};