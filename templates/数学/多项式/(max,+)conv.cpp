vector<int> merge(vector<int> &a, vector<int> &b) {
	vector<int> c {a[0] + b[0]};
	int i = 1, j = 1;
	for ( ; i < a.size() && j < b.size(); ) {
		if (a[i] + b[j - 1] > a[i - 1] + b[j]) {
			c.push_back(a[i] + b[j - 1]);
			i++;
		} else {
			c.push_back(a[i - 1] + b[j]);
			j++;
		}
	}
	for ( ; i < a.size(); i++) {
		c.push_back(a[i] + b.back());
	}
	for ( ; j < b.size(); j++) {
		c.push_back(a.back() + b[j]);
	}
	return c;
}