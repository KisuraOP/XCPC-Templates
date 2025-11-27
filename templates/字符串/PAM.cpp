struct PAM {
	static constexpr int S = 26;
	int tot, lst;
	string s;
	vector<array<int, S>> ch;
	vector<int> fail, len, cnt;
	PAM(int n) : tot(-1), lst(0), fail(2 * n + 1), 
	len(2 * n + 1), cnt(2 * n + 1), ch(2 * n + 1) {
		init();
	}
	void init() {
		s += '@';
		len[++tot] = 0;
		len[++tot] = -1;
		fail[0] = 1;
	}
	int getfail(int pos, int x) {
		while (s[pos] != s[pos - len[x] - 1]) {
			x = fail[x];
		}
		return x;
	}
	void insert(int pos, int x) {
		s += ('a' + x);
		int o = getfail(pos, lst);
		if (!ch[o][x]) {
			tot++;
			fail[tot] = ch[getfail(pos, fail[o])][x];
			ch[o][x] = tot;
			len[tot] = len[o] + 2;
		}
		lst = ch[o][x];
		cnt[lst]++;
	}
	int size() {
		return tot;
	}
};

/*
例：记 cnt[T] 为 T 在 S 中的出现次数。
给定 S，对所有回文子串 T，求 max_{T}(cnt[T] \cdot |T|^2)。

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
*/

/*
例：给定 S，对 i\in[1, n] 求以 S_i 结尾的回文子串个数，强制在线。

int insert(int pos, int x) {
	s += ('a' + x);
	int o = getfail(pos, lst);
	if (!ch[o][x]) {
		tot++;
		fail[tot] = ch[getfail(pos, fail[o])][x];
		ch[o][x] = tot;
		len[tot] = len[o] + 2;
		cnt[tot] = cnt[fail[tot]] + 1;
	}
	lst = ch[o][x];
	return cnt[lst];
}

void solve() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	PAM t(n);
	for (int i = 1; i <= n; i++) {
		cout << t.insert(i, s[i] - 'a') << "\n";
	}
}
*/