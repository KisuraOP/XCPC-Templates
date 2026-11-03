// 依赖 KMP.cpp。
/*
vector<int> ans = match(a, b);
寻找字符串 b 在字符串 a 中的出现位置，储存在 ans 中。
字符串 1-index。
*/

vector<int> match(string a, string b) {
	int ha = a.size() - 1;
	int hb = b.size() - 1;
	auto nxt = KMP(b);
	vector<int> ans;
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
	return ans;
};
