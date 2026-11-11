/*
auto seg = lyndon(s);
返回 Lyndon 分解中各段的闭区间，O(n)。
*/
vector<array<int, 2>> lyndon(const string &s) {
    int n = s.size() - 1;
    vector<array<int, 2>> ans;
    for (int i = 1; i <= n;) {
        int j = i + 1, k = i;
        while (j <= n && s[k] <= s[j]) {
            k = s[k] < s[j] ? i : k + 1;
            j++;
        }
        while (i <= k) {
            ans.push_back({i, i + j - k - 1});
            i += j - k;
        }
    }
    return ans;
}
