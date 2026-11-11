/*
int ans = half(w, v, m);
每件物品至多选一次，返回总重量不超过 m 的最大价值。
适合物品数较少、容量很大的情形，时间复杂度 O(n 2^(n/2))。
*/
int half(const vector<int> &w, const vector<int> &v, int m) {
    int n = w.size() - 1;
    auto gen = [&](int l, int r) {
        vector<array<int, 2>> a{{0, 0}};
        for (int i = l; i <= r; i++) {
            for (int j = a.size() - 1; j >= 0; j--) {
                if (a[j][0] + w[i] <= m) {
                    a.push_back({a[j][0] + w[i], a[j][1] + v[i]});
                }
            }
        }
        sort(a.begin(), a.end());
        for (int i = 1; i < a.size(); i++) {
            a[i][1] = max(a[i][1], a[i - 1][1]);
        }
        return a;
    };
    auto a = gen(1, n / 2), b = gen(n / 2 + 1, n);
    int ans = 0, j = b.size() - 1;
    for (auto x : a) {
        while (x[0] + b[j][0] > m) {
            j--;
        }
        ans = max(ans, x[1] + b[j][1]);
    }
    return ans;
}
