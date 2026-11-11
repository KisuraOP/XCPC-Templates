// 依赖 SA_LCP.cpp。
// 比较 s[l..r] 与 s[x..y]，返回 -1、0、1，O(1)。
int cmp(const string &s, LCP &q, int l, int r, int x, int y) {
    int a = r - l + 1, b = y - x + 1, k = q.lcp(l, x);
    if (k >= min(a, b)) {
        return (a > b) - (a < b);
    }
    return s[l + k] < s[x + k] ? -1 : 1;
}

// 统计非空不同子串，O(n)。
int count(LCP &q) {
    int ans = 0;
    for (int i = 1; i <= q.n; i++) {
        ans += q.n - q.sa[i] + 1 - q.ht[i];
    }
    return ans;
}
