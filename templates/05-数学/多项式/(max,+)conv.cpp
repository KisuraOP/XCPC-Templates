// c[k] = \max_{k = i + j + t} (a[i] + b[j])
vector<int> merge(const vector<int> a, const vector<int> b) {
	vector<int> c {a[0] + b[0]};
	int i = 1, j = 1;
	while (i < a.size() && j < b.size()) {
		if (a[i] + b[j - 1] > a[i - 1] + b[j]) {
			c.push_back(a[i] + b[j - 1]);
			i++;
		} else {
			c.push_back(a[i - 1] + b[j]);
			j++;
		}
	}
	while (i < a.size()) {
		c.push_back(a[i] + b.back());
		i++;
	}
	while (j < b.size()) {
		c.push_back(a.back() + b[j]);
		j++;
	}
	return c;
}