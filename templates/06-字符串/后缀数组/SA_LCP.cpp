// 依赖 SA.cpp 或 SA_IS.cpp。
/*
LCP q(s); 或 LCP q(a, m);
预处理 O(n log n + m)。
rk[i] 为后缀 i 的排名，ht[i] 为相邻两个后缀 sa[i - 1]、sa[i] 的最长公共前缀长度。
ht[1] = 0，参数约定同 suffix。

q.lcp(i, j);
返回后缀 i 与后缀 j 的最长公共前缀长度，O(1)。
允许 i、j 为 n + 1，表示空后缀。
*/
struct LCP {
    int n;
    vector<int> sa, rk, ht;
    vector<vector<int>> q;
    LCP(const vector<int> &s, vector<int> a) : n(s.size() - 1),
        sa(move(a)), rk(n + 1), ht(n + 1) {
        for (int i = 1; i <= n; i++) {
            rk[sa[i]] = i;
        }
        for (int i = 1, k = 0; i <= n; i++) {
            if (rk[i] == 1) {
                k = 0;
                continue;
            }
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) {
                k++;
            }
            ht[rk[i]] = k;
            k -= k > 0;
        }
        q.push_back(ht);
        for (int k = 0; (2LL << k) <= n; k++) {
            q.emplace_back(n + 1);
            for (int i = 1; i + (2LL << k) - 1 <= n; i++) {
                q[k + 1][i] = min(q[k][i], q[k][i + (1LL << k)]);
            }
        }
    }
    LCP(const vector<int> &s, int m) : LCP(s, suffix(s, m)) {}
    LCP(const string &s) : LCP(vector<int>(s.begin(), s.end()), suffix(s)) {}
    int lcp(int i, int j) {
        if (i == j) {
            return n - i + 1;
        }
        if (i > n || j > n) {
            return 0;
        }
        int l = min(rk[i], rk[j]) + 1, r = max(rk[i], rk[j]);
        int k = __lg(r - l + 1);
        return min(q[k][l], q[k][r - (1LL << k) + 1]);
    }
};
