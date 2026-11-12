/*
auto [f, p] = knuth(n, w);
f[l][r] 为区间最小合并费用，单点费用为 0。
合并 [l, r] 的额外费用为 w(l, r)。

p[l][r] 记录最优分割点，费用相同时取最大的 k，要求满足
p[l][r - 1] <= p[l][r] <= p[l + 1][r]。
*/
template<class W>
array<vector<vector<int>>, 2> knuth(int n, W w) {
    vector<vector<int>> f(n + 1, vector<int>(n + 1)), p = f;
    for (int i = 1; i <= n; i++) {
        p[i][i] = i;
    }
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1, c = w(l, r);
            f[l][r] = inf;
            for (int k = p[l][r - 1]; k <= min(r - 1, p[l + 1][r]); k++) {
                int v = f[l][k] + f[k + 1][r] + c;
                if (v <= f[l][r]) {
                    f[l][r] = v;
                    p[l][r] = k;
                }
            }
        }
    }
    return {move(f), move(p)};
}
