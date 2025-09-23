auto merge = [&] (const array<int, 2> &x, const array<int, 2> &y) -> array<int, 2> {
	if (!x[0] || !y[0]) {
		return {0ll, 0ll};
	}
	int d[4], c[2];
	d[0] = G.LCA(x[0], y[0]);
	d[1] = G.LCA(x[0], y[1]);
	d[2] = G.LCA(x[1], y[0]);
	d[3] = G.LCA(x[1], y[1]);
	c[0] = G.LCA(x[0], x[1]);
	c[1] = G.LCA(y[0], y[1]);
	sort(d, d + 4, [&] (const int &i, const int &j) {
		return G.dep[i] < G.dep[j];
	});
	sort(c, c + 2, [&] (const int &i, const int &j) {
		return G.dep[i] < G.dep[j];
	});
	if (G.dep[c[0]] <= G.dep[d[0]] && G.dep[c[1]] <= G.dep[d[2]]) {
		return {d[2], d[3]};
	}
	return {0ll, 0ll};
};