// 依赖后缀数组中的 SA_LCP.cpp。
/*
auto ans = runs(s);
返回所有 Run 的 {l, r, p}，按此顺序排序，无重复，O(n log n)。
*/
vector<array<int, 3>> runs(const string &s) {
    int n = s.size() - 1;
    string t = s;
    reverse(t.begin() + 1, t.end());
    LCP f(s), b(t);
    vector<array<int, 3>> ans;
    for (int z = 0; z < 2; z++) {
        vector<int> st{n + 1};
        for (int i = n; i >= 1; i--) {
            while (st.size() > 1) {
                int j = st.back(), k = f.lcp(i, j);
                if (j + k > n || (s[i + k] < s[j + k]) == z) {
                    break;
                }
                st.pop_back();
            }
            int j = st.back(), p = j - i;
            int l = b.lcp(n - i + 2, n - j + 2), r = f.lcp(i, j);
            if (l + r >= p) {
                ans.push_back({i - l, j + r - 1, p});
            }
            st.push_back(i);
        }
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    return ans;
}
