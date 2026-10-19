/*
p: prufer 序列, 0-index。
e: 无向边集, 顶点编号 1..n, n >= 2。
*/
vector<int> Tree2Prufer(vector<array<int, 2>> e, int n) {
	vector<int> d(n + 1), s(n + 1), p(n - 2); // s 为邻点编号的异或和
	for (auto [x, y] : e) {
		d[x]++, d[y]++;
		s[x] ^= y, s[y] ^= x;
	}
	for (int i = 0, j = 1; i < n - 2; i++, j++) {
		while (j <= n && d[j] != 1) {
			j++;
		}
		p[i] = s[j];
		s[p[i]] ^= j;
		while (i < n - 3 && --d[p[i]] == 1 && p[i] < j) {
			p[i + 1] = s[p[i]];
			s[p[i + 1]] ^= p[i];
			i++;
		}
	}
	return p;
}
vector<array<int, 2>> Prufer2Tree(vector<int> p, int n) {
	vector<int> d(n + 1, 1);
	vector<array<int, 2>> e(n - 1);
	for (auto x : p) {
		d[x]++;
	}
	p.push_back(n);
	for (int i = 0, j = 1; i < n - 1; i++, j++) {
		while (j <= n && d[j] > 1) {
			j++;
		}
		e[i] = {j, p[i]};
		while (i < n - 2 && --d[p[i]] == 1 && p[i] < j) {
			e[i + 1] = {p[i], p[i + 1]};
			i++;
		}
	}
	return e;
}