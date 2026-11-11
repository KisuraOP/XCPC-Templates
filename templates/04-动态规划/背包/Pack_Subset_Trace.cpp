/*
auto a = subset(w, s);
返回凑出重量 s 的一组物品编号，每件至多选一次。
若无解则返回 {-1}。
*/
vector<int> subset(const vector<int> &w, int s) {
    bitset<N> f(1);
    vector<int> pre(s + 1), a;
    for (int i = 1; i < w.size(); i++) {
        auto g = (f << w[i]) & ~f;
        for (int j = g._Find_first(); j <= s; j = g._Find_next(j)) {
            pre[j] = i;
        }
        f |= g;
    }
    if (!f[s]) {
        return {-1};
    }
    while (s) {
        int i = pre[s];
        a.push_back(i);
        s -= w[i];
    }
    reverse(a.begin(), a.end());
    return a;
}
