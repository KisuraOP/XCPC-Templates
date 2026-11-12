/*
vector<int> nxt = KMP(a);
nxt[i] 为 a 的前 i 个字符的最长 border 长度。
border 指既是前缀又是后缀、且长度小于原串的子串。

*/

vector<int> KMP(string a) {
	int n = a.size() - 1;
	vector<int> nxt(n + 1);
	for (int i = 2, p = 0; i <= n; i++) {
		while (p && a[i] != a[p + 1]) {
			p = nxt[p];
		}
		if (a[i] == a[p + 1]) {
			p++;
		}
		nxt[i] = p;
	}
	return nxt;
}

