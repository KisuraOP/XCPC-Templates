vector<vector<int>> f(n + 1, vector<int>(n + 1));
for (int i = 1; i <= n; i++) {
    f[i][i] = 1;
}
for (int len = 2; len <= n; len++) {
    for (int l = 1; l + len - 1 <= n; l++) {
        int r = l + len - 1;
        if (a[l] == a[r]) {
            f[l][r] = f[l + 1][r - 1] + 2;
        } else {
            f[l][r] = max(f[l + 1][r], f[l][r - 1]);
        }
    }
}
int ans = f[1][n];
