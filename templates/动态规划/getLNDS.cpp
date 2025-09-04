auto LNDS = [&] (vector<int> &a) -> int {
	vector<int> d;
	for (auto x : a) {
		auto it = upper_bound(d.begin(), d.end(), x);
		if (it == d.end()) {
			d.push_back(x);
		} else {
			*it = x;
		}
	}
	return d.size();
};