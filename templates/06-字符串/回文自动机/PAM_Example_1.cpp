// 依赖 PAM.cpp。
/*
例：记 cnt[T] 为 T 在 S 中的出现次数。
给定 S，对所有回文子串 T，求 max_{T}(cnt[T] \cdot |T|^2)。
*/

void solve() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	PAM t(n);
	for (int i = 1; i <= n; i++) {
		t.insert(i, s[i] - 'a');
	}
	for (int i = t.size(); i >= 1; i--) {
		t.cnt[t.fail[i]] += t.cnt[i];
	}
	int ans = 0;
	for (int i = 1; i <= t.size(); i++) {
		ans = max(ans, t.len[i] * t.len[i] * t.cnt[i]);
	}
	cout << ans << "\n";
}
