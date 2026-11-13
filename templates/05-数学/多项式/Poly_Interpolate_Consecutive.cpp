/*
lagran(y, x, iv);
y[i] = f(i)，f 的次数小于 n，返回 f(x) mod mod，O(n)。
采样点模 mod 互异，iv[i] 为 i! 的逆元，准备到 n-1。

用组合数中的 Comb.cpp 准备逆阶乘：
binom.init(y.size() - 2);
cout << lagran(y, x, binom.inv);
*/
int lagran(const vector<int> &y, int x, const vector<int> &iv) {
    int n = y.size() - 1;
    x = (x % mod + mod) % mod;
    vector<int> pre(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] * (x - i + mod) % mod;
    }
    int ans = 0, suf = 1;
    for (int i = n; i; i--) {
        int v = y[i] * pre[i - 1] % mod * suf % mod * iv[i - 1] % mod * iv[n - i] % mod;
        ans = (ans + ((n - i) % 2 ? mod - v : v)) % mod;
        suf = suf * (x - i + mod) % mod;
    }
    return (ans + mod) % mod;
}
