/*
zero(f, w, v); 加入一件重量 w、价值 v 的物品。
full(f, w, v); 加入重量 w、价值 v、数量不限的物品。
两者均为 O(m)。

group(f, a); 加入一组物品，至多选一件。
a[i] = {重量, 价值}，时间复杂度 O(m * 组内物品数)。
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
