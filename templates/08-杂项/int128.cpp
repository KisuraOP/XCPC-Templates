istream &operator>>(istream &is, __int128 &n) {
	string s;
	is >> s;
	n = 0;
	bool neg = false;
	if (!s.empty() && s[0] == '-') {
		neg = true;
		s = s.substr(1);
	}
	for (char c : s) { 
		n = n * 10 + (c - '0');
	}
	if (neg) {
		n = -n;
	}
	return is;
}
ostream &operator<<(ostream &os, __int128 n) {
	if (n == 0) {
		return os << 0;
	}
	if (n < 0) {
		os << "-";
		n = -n;
	}
	string s;
	while (n > 0) { 
		s += char('0' + n % 10); 
		n /= 10;
	}
	reverse(s.begin(), s.end());
	return os << s;
}