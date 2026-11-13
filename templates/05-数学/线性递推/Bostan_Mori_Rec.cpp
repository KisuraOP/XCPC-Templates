/*
依赖 Bostan_Mori.cpp。

linrec(a, c, n);
初值和系数约定同 linear，返回第 n 项，O(k log k log n)。
可直接使用 bm(a) 返回的系数。
*/
int linrec(const vector<int> &a, const vector<int> &c, int n) {
    if (n < a.size()) {
        return a[n];
    }
    int k = c.size() - 1;
    if (!k) {
        return 0;
    }
    vector<int> p(a.begin() + 1, a.begin() + k + 1), q(k + 1);
    q[0] = 1;
    for (int i = 1; i <= k; i++) {
        q[i] = (mod - c[i]) % mod;
    }
    p = p * q;
    p.resize(k);
    return bostan(p, q, n - 1);
}
