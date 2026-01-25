/*
选取一组两两互质的基, 存储在 {p} 中。
满足所有向量都能被基向量的幂的乘积唯一表示。

基的大小: |basis| = O(nw)。
n 为插入次数, w 为不同质因数个数。
时间复杂度: O(n|basis|)。
*/
struct Basis {
	vector<int> p;
	Basis() {}
	void insert(int x) {
		if (x <= 1) {
			return ;
		}
		queue<int> q;
		q.push(x);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			if (v <= 1) {
				continue;
			}
			bool f = false;
			for (int i = 0; i < p.size(); i++) {
				int b = p[i];
				int g = __gcd(v, b);
				if (g > 1) {
					p[i] = p.back();
					p.pop_back();
					if (v / g > 1) {
						q.push(v / g);
					}
					if (b / g > 1) {
						q.push(b / g);
					}
					q.push(g);
					f = true;
					break;
				}
			}
			if (!f) {
				p.push_back(v);
			}
		}
	}
};