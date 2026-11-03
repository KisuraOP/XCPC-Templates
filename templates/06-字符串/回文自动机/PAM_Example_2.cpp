// 本项包含专用 PAM，单独使用。
/*
例：给定 S，对 i\in[1, n] 求以 S_i 结尾的回文子串个数，强制在线。
*/

struct PAM {
	static constexpr int S = 26;
	int tot, lst;
	string s;
	vector<array<int, S>> ch;
	vector<int> fail, len, cnt;
	PAM(int n) : tot(-1), lst(0), fail(n + 2), 
	len(n + 2), cnt(n + 2), ch(n + 2) {
		init();
	}
	void init() {
		tot = -1;
		lst = 0;
		s = "@";
		ch.assign(ch.size(), {});
		cnt.assign(cnt.size(), 0);
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
	int size() {
		return tot;
	}
};

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
