/*
vector<int> nxt = KMP(a);
nxt[i]: 一个字符串中长度为 i 的前缀的最长 border 长度。
border: s 的一个非 s 本身的子串 t, 既是 s 的前缀又是 s 的后缀。
字符串 1-index。

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

