// 依赖 PAM.cpp。
/*
例：给定 S，对 i\in[1, n] 求以 S_i 结尾的回文子串个数，强制在线。
*/

void solve() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	PAM t(n);
	vector<int> dep(n + 2);
	for (int i = 1; i <= n; i++) {
		t.insert(i, s[i] - 'a');
		dep[t.lst] = dep[t.fail[t.lst]] + 1;
		cout << dep[t.lst] << "\n";
	}
}
