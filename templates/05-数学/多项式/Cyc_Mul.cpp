vector<Z> operator*(const vector<Z> &a, const vector<Z> &b) {
	const int k = a.size();
	vector<Z> z(k);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			z[(i + j) % k] += a[i] * b[j];
		}
	} 
	return z;
}

vector<Z> qpow(vector<Z> a, int n) {
	vector<Z> s(a.size());
	s[0] = 1;
	for ( ; n; n >>= 1, a = a * a) {
		if (n & 1) s = s * a;
	}
	return s;
}