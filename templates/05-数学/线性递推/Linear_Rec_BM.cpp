/*
auto c = bm(a);
返回满足给定前缀 a 的最短线性递推系数，mod 为质数。
全零前缀返回零阶递推 c = {0}。
m 项前缀的时间复杂度 O(m^2 + m log mod)。

配合 Linear_Rec.cpp：
vector<int> a = {0, 1, 1, 2, 3, 5, 8};
auto c = bm(a); // {0, 1, 1}
cout << linear(a, c, 10); // 55
*/
vector<int> bm(const vector<int> &a) {
    auto power = [&](int x, int n) {
        int r = 1;
        for (; n; n >>= 1, x = x * x % mod) {
            if (n & 1) {
                r = r * x % mod;
            }
        }
        return r;
    };
    vector<int> c{1}, b{1};
    int k = 0, d = 1, inv = 1;
    for (int n = 1; n < a.size(); n++) {
        int v = a[n];
        for (int i = 1; i <= k; i++) {
            v = (v + c[i] * a[n - i]) % mod;
        }
        if (!v) {
            d++;
            continue;
        }
        auto t = c;
        int w = v * inv % mod;
        c.resize(max<int>(c.size(), b.size() + d));
        for (int i = 0; i < b.size(); i++) {
            c[i + d] = (c[i + d] - w * b[i] % mod + mod) % mod;
        }
        if (2 * k < n) {
            k = n - k;
            b = t;
            inv = power(v, mod - 2);
            d = 1;
        } else {
            d++;
        }
    }
    c.resize(k + 1);
    for (auto &x : c) {
        x = (mod - x) % mod;
    }
    c[0] = 0;
    return c;
}
