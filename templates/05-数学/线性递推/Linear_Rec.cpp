/*
int ans = linear(a, c, n);
c[1..k] 为递推系数，a 至少包含前 k 项，返回第 n 项。
时间复杂度 O(k^2 log n)。
*/
int linear(const vector<int> &a, const vector<int> &c, int n) {
    if (n < a.size()) {
        return a[n];
    }
    int k = c.size() - 1;
    if (!k) {
        return 0;
    }
    auto mul = [&](const vector<int> &a, const vector<int> &b) {
        vector<int> v(2 * k - 1);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                v[i + j] = (v[i + j] + a[i] * b[j]) % mod;
            }
        }
        for (int i = 2 * k - 2; i >= k; i--) {
            for (int j = 1; j <= k; j++) {
                v[i - j] = (v[i - j] + v[i] * c[j]) % mod;
            }
        }
        v.resize(k);
        return v;
    };
    vector<int> f(k), g(k);
    f[0] = 1;
    if (k == 1) {
        g[0] = c[1];
    } else {
        g[1] = 1;
    }
    for (n--; n; n >>= 1, g = mul(g, g)) {
        if (n & 1) {
            f = mul(f, g);
        }
    }
    int ans = 0;
    for (int i = 0; i < k; i++) {
        ans = (ans + f[i] * a[i + 1]) % mod;
    }
    return ans;
}
