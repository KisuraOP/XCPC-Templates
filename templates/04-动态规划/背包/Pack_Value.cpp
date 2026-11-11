/*
value(f, w, v); 加入一件重量为 w、价值为 v 的物品，要求 v >= 0。
f[j] 为价值恰为 j 的最小重量，初始化 f[0] = 0，其余为 inf。

容量为 m 时，答案为满足 f[j] <= m 的最大 j。
取价值总和 S 为状态上限，处理 n 件物品共 O(nS)。
*/
void value(vector<int> &f, int w, int v) {
    for (int j = f.size() - 1; j >= v; j--) {
        if (f[j - v] != inf) {
            f[j] = min(f[j], f[j - v] + w);
        }
    }
}
