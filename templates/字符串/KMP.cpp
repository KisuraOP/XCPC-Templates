/*
vector<int> nxt = KMP(a, b);
寻找字符串 b 在字符串 a 中的出现位置，储存在 ans 中，并返回 b 的 nxt 数组。
nxt[i]: 一个字符串中长度为 i 的前缀的最长 border 长度。
border: s 的一个非 s 本身的子串 t, 既是 s 的前缀又是 s 的后缀。
*/

// find b in a (all 1-index)
vector<int> ans;
auto KMP = [&] (string a, string b) {
	int ha = a.size() - 1;
	int hb = b.size() - 1;

	vector<int> nxt(hb + 1);
	for (int i = 2, p = 0; i <= hb; i++) {
		while (p && b[i] != b[p + 1]) {
			p = nxt[p];
		}
		if (b[i] == b[p + 1]) {
			p++;
		}
		nxt[i] = p;
	}
	for (int i = 1, p = 0; i <= ha; i++) {
		while (p && a[i] != b[p + 1]) {
			p = nxt[p];
		}
		if (a[i] == b[p + 1]) {
			p++;
		}
		if (p == hb) {
			ans.push_back(i - hb + 1);
			p = nxt[p];
		}
	}
	return nxt;
};