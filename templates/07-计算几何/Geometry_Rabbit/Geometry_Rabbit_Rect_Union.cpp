/*
int ans = area(a);
a[i] = {x1, y1, x2, y2}，为轴对齐矩形的左下角、右上角。
整数坐标，返回面积并；零面积矩形不影响结果。
时间复杂度 O(n log n)。
*/
int area(const vector<array<int, 4>> &a) {
    vector<array<int, 4>> e;
    vector<int> y;
    for (int i = 1; i < a.size(); i++) {
        auto [l, b, r, t] = a[i];
        if (l == r || b == t) {
            continue;
        }
        e.push_back({l, b, t, 1});
        e.push_back({r, b, t, -1});
        y.push_back(b);
        y.push_back(t);
    }
    if (e.empty()) {
        return 0;
    }
    sort(e.begin(), e.end());
    sort(y.begin(), y.end());
    y.erase(unique(y.begin(), y.end()), y.end());
    int n = y.size() - 1;
    vector<int> cnt(4 * n + 4), len(4 * n + 4);
    auto add = [&](auto self, int p, int l, int r, int L, int R, int v) -> void {
        if (L <= l && r <= R) {
            cnt[p] += v;
        } else {
            int mid = (l + r) / 2;
            if (L <= mid) {
                self(self, p * 2, l, mid, L, R, v);
            }
            if (R > mid) {
                self(self, p * 2 + 1, mid + 1, r, L, R, v);
            }
        }
        if (cnt[p]) {
            len[p] = y[r] - y[l - 1];
        } else {
            len[p] = l == r ? 0 : len[p * 2] + len[p * 2 + 1];
        }
    };
    int ans = 0, pre = e[0][0];
    for (auto [x, b, t, v] : e) {
        ans += (x - pre) * len[1];
        int l = lower_bound(y.begin(), y.end(), b) - y.begin() + 1;
        int r = lower_bound(y.begin(), y.end(), t) - y.begin();
        add(add, 1, 1, n, l, r, v);
        pre = x;
    }
    return ans;
}
