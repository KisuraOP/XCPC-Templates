/*
auto sa = suffix(s);
sa[i] 为字典序第 i 小的后缀起点。

auto sa = suffix(a, m);
a 为整数序列，取值在 [1, m]。倍增构建 O(n log n + m)。
与 SA_IS.cpp 选择一份使用。
*/
vector<int> suffix(const vector<int> &s, int m) {
    int n = s.size() - 1;
    vector<int> sa(n + 1), x = s, y(n + 1), c(max(n, m) + 1);
    iota(sa.begin(), sa.end(), 0);
    for (int k = 0, p = 0; p < n; k = k ? k * 2 : 1, m = p) {
        p = 0;
        for (int i = n - k + 1; i <= n; i++) {
            y[++p] = i;
        }
        for (int i = 1; i <= n; i++) {
            if (sa[i] > k) {
                y[++p] = sa[i] - k;
            }
        }
        fill(c.begin(), c.begin() + m + 1, 0);
        for (int i = 1; i <= n; i++) {
            c[x[i]]++;
        }
        for (int i = 1; i <= m; i++) {
            c[i] += c[i - 1];
        }
        for (int i = n; i >= 1; i--) {
            sa[c[x[y[i]]]--] = y[i];
        }
        x.swap(y);
        p = x[sa[1]] = 1;
        for (int i = 2; i <= n; i++) {
            int a = sa[i - 1], b = sa[i];
            p += y[a] != y[b] ||
                (a + k <= n ? y[a + k] : 0) != (b + k <= n ? y[b + k] : 0);
            x[b] = p;
        }
    }
    return sa;
}
vector<int> suffix(const string &s) {
    vector<int> a(s.size());
    for (int i = 1; i < s.size(); i++) {
        a[i] = s[i] + 1;
    }
    return suffix(a, 128);
}
