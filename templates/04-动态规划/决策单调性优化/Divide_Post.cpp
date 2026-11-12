// 依赖 Divide.cpp，x 已按非递减顺序排列。
vector<int> s(n + 1);
for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + x[i];
}
auto w = [&](int l, int r) {
    int k = (l + r) / 2;
    return x[k] * (k - l + 1) - (s[k] - s[l - 1])
        + (s[r] - s[k]) - x[k] * (r - k);
};
auto f = divide(n, m, w);
int ans = f[n];
