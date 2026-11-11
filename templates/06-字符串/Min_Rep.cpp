/*
int p = minrep(s);
返回非空串 s 的最小循环移位起点，O(n)。
若有多个相同的最小循环移位，则返回最小起点。
*/
int minrep(const string &s) {
    int n = s.size() - 1, i = 1, j = 2, k = 0;
    while (i <= n && j <= n && k < n) {
        int a = s[(i + k - 1) % n + 1], b = s[(j + k - 1) % n + 1];
        if (a == b) {
            k++;
        } else {
            if (a > b) {
                i += k + 1;
            } else {
                j += k + 1;
            }
            if (i == j) {
                j++;
            }
            k = 0;
        }
    }
    return min(i, j);
}
