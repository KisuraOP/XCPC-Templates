// 依赖 Knuth.cpp。
vector<int> s(n + 1);
for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + a[i];
}
auto [f, p] = knuth(n, [&](int l, int r) {
    return s[r] - s[l - 1];
});
int ans = f[1][n];
