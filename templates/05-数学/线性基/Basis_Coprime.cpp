/*
构造一组两两互质的数，存入 bs。
每个输入的数都能唯一表示为 bs 中各数的非负整数次幂之积。

基的大小: |bs| = O(nw)。
n 为插入次数, w 为不同质因数个数。
时间复杂度: O(n * |bs|)。
*/
struct Basis {
	vector<int> bs;
	Basis() {}
	void insert(int x) {
		for (auto p : bs) {
			while (x % p == 0) {
				x /= p;
			}
		}
		if (x == 1) {
			return ;
		}
		for (int i = 0; i < bs.size(); i++) {
			int p = bs[i];
			int g = __gcd(x, p);
			if (g != 1) {
				swap(bs[i], bs.back());
				bs.pop_back();
				insert(x / g);
				insert(p / g);
				insert(g);
				return ;
			}
		}
		bs.push_back(x);
	}
};