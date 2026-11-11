/*
auto f = subset(w);
每件物品至多选一次，f[s] 表示能否凑出重量 s。
*/
bitset<N> subset(const vector<int> &w) {
    bitset<N> f(1);
    for (int i = 1; i < w.size(); i++) {
        f |= f << w[i];
    }
    return f;
}
