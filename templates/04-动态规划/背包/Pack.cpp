/*
zero(f, w, v); 01 背包。
full(f, w, v); 完全背包。
w 为重量，v 为价值。两种操作均为 O(m)。

group(f, a); 加入一组物品，至多选一件。
a[i] = {重量, 价值}，O(m * 组内物品数)。
*/
void zero(vector<int> &f, int w, int v) {
    for (int j = f.size() - 1; j >= w; j--) {
        if (f[j - w] != -inf) {
            f[j] = max(f[j], f[j - w] + v);
        }
    }
}
void full(vector<int> &f, int w, int v) {
    for (int j = w; j < f.size(); j++) {
        if (f[j - w] != -inf) {
            f[j] = max(f[j], f[j - w] + v);
        }
    }
}
void group(vector<int> &f, const vector<array<int, 2>> &a) {
    for (int j = f.size() - 1; j >= 0; j--) {
        for (int i = 1; i < a.size(); i++) {
            int w = a[i][0], v = a[i][1];
            if (j >= w && f[j - w] != -inf) {
                f[j] = max(f[j], f[j - w] + v);
            }
        }
    }
}
