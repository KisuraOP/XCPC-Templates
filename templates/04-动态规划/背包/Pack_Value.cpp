/*
value(f, w, v); 加入一件重量 w、非负整数价值 v 的物品。
f[j] 为价值恰好等于 j 的最小重量，初始化 f[0] = 0，其余为 inf。
若无法达到价值 j，则 f[j] = inf。

容量为 m 时，答案为满足 f[j] <= m 的最大 j。
通常将 f 开到价值总和 S，n 件物品共 O(nS)。
*/
void value(vector<int> &f, int w, int v) {
    for (int j = f.size() - 1; j >= v; j--) {
        if (f[j - v] != inf) {
            f[j] = min(f[j], f[j - v] + w);
        }
    }
}
