/*
依赖 CHT.cpp。

auto f = dp(s, c);
s 非递减，计算 f[1] = 0，f[i] = min(f[j] + (s[i] - s[j])^2 + c)，1 <= j < i。
时间复杂度 O(n)。

示例：dp({0, 1, 3, 6}, 2) 返回 {0, 0, 6, 17}。
若 s 不单调，改用 CHT_Dynamic.cpp，并将 mono 改为 query，时间复杂度 O(n log n)。
*/
vector<int> dp(const vector<int> &s, int c) {
    vector<int> f(s.size());
    CHT q;
    q.insert({2 * s[1], -s[1] * s[1]});
    for (int i = 2; i < s.size(); i++) {
        f[i] = s[i] * s[i] + c - q.mono(s[i]);
        q.insert({2 * s[i], -f[i] - s[i] * s[i]});
    }
    return f;
}
