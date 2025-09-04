auto getLCS = [&] (string s, string t) {
	int n = s.size();
	int m = t.size();
	vector dp(n + 1, vector<int>(m + 1));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s[i - 1] == t[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	string res;
	int p = n, q = m;
	while (p > 0 && q > 0) {
		if (s[p - 1] == t[q - 1]) {
			res += s[p - 1];
			p--;
			q--;
		} else if (dp[p - 1][q] > dp[p][q - 1]) {
			p--;
		} else {
			q--;
		}
	}
	reverse(res.begin(), res.end());
	return res;
};