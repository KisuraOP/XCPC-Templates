vector<int> s(n + 1);
vector<vector<int>> f(n + 1, vector<int>(n + 1)), p = f;
for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + a[i];
    p[i][i] = i;
}
for (int len = 2; len <= n; len++) {
    for (int l = 1; l + len - 1 <= n; l++) {
        int r = l + len - 1;
        f[l][r] = inf;
        for (int k = l; k < r; k++) {
            int v = f[l][k] + f[k + 1][r] + s[r] - s[l - 1];
            if (v <= f[l][r]) {
                f[l][r] = v;
                p[l][r] = k;
            }
        }
    }
}
int ans = f[1][n];
