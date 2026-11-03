// 依赖 SAM.cpp。
/*
使用例： 求 S 的所有出现次数大于 1 的子串的 (出现次数 * 长度) 的最大值。
*/

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    SAM t;
    int p = 1;
    vector<int> cnt(2 * n + 10);
    for (auto c : s) {
        p = t.extend(p, c - 'a');
        cnt[p]++;
    }
    
    n = t.size();
    vector<int> o(n);
    iota(o.begin(), o.end(), 0);
    sort(o.begin(), o.end(), [&] (int x, int y) {
        return t.len(x) > t.len(y);
    });

    for (auto x : o) {
        if (t.link(x) > 0) {
            cnt[t.link(x)] += cnt[x];
        }
    }

    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (cnt[i] > 1) {
            ans = max(ans, t.len(i) * cnt[i]);
        }
    }
    cout << ans << "\n";
}
