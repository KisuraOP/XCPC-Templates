// 0-index
// z[i] : longgest prefix of [0, n - 1] and [i, n - 1]
vector<int> z_function(string s) {
	vector<int> z(s.size());
	for (int i = 1, l = 0; i < s.size(); i++) {
		if (l + z[l] > i) {
			z[i] = min(z[i - l], l + z[l] - i);
		}
		while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
			z[i]++;
		}
		if (i + z[i] > l + z[l]) {
			l = i;
		}
	}
	return z;
}