vector<array<int, 3>> qry(q);
for (int i = 0; i < q; i++) {
	int l, r;
	cin >> l >> r;
	qry[i] = {l, r, i};
}

int sz = n / sqrtl(1.0 * q * 2 / 3) + 1;

sort(qry.begin(), qry.end(), 
	[&] (array<int, 3> i, array<int, 3> j) {
	if (i[0] / sz == j[0] / sz) {
		if ((i[0] / sz) % 2 == 0) {
			return i[1] > j[1];
		} else {
			return i[1] < j[1];
		}
	} else {
		return i[0] / sz < j[0] / sz;
	}
});

auto add = [&] (int x) {
};
auto del = [&] (int x) {
};

vector<int> ans(q);
int l = 1, r = 0;
for (int i = 0; i < q; i++) {
	auto [ql, qr, id] = qry[i];
	while (l > ql) {
		add(--l);
	}
	while (r < qr) {
		add(++r);
	}
	while (l < ql) {
		del(l++);
	}
	while (r > qr) {
		del(r--);
	}
	ans[id] = res;
}