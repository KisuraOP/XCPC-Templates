/*
p: prufer 序列, 0-index。
fa: 父亲序列, 1-index。
*/
vector<int> Tree2Prufer(vector<int> fa, int n) {
	vector<int> d(n + 1), p(n - 2);
	for (auto x : fa) {
		d[x]++;
	}
	for (int i = 0, j = 1; i < n - 2; i++, j++) {
		while (j <= n && d[j]) {
			j++;
		}
		p[i] = fa[j];
		while (i < n - 3 && !--d[p[i]] && p[i] < j) {
			p[i + 1] = fa[p[i]];
			i++;
		}
	}
	return p;
}
vector<int> Prufer2Tree(vector<int> p, int n) {
	vector<int> d(n + 1, 1), fa(n + 1);
	for (auto x : p) {
		d[x]++;
	}
	p.push_back(n);
	for (int i = 0, j = 1; i < n - 1; i++, j++) {
		while (j <= n && d[j] > 1) {
			j++;
		}
		fa[j] = p[i];
		while (i < n - 2 && --d[p[i]] == 1 && p[i] < j) {
			fa[p[i]] = p[i + 1];
			i++;
		}
	}
	return fa;
}