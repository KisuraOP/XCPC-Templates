/*
mixed() 演示混合背包，依赖 Pack.cpp 及任一 multi，返回 15。

zero(f, w, u, v); 加入一件两种费用分别为 w、u，价值为 v 的物品。
两种费用均为非负整数；f 开为 (m + 1) * (k + 1)。
恰好装满时初始化 f[0][0] = 0，其余为 -inf，时间复杂度 O(mk)。
*/
int mixed() {
    vector<int> f(11, -inf);
    f[0] = 0;
    zero(f, 2, 3);
    full(f, 3, 4);
    multi(f, 4, 6, 2);
    return *max_element(f.begin(), f.end());
}
void zero(vector<vector<int>> &f, int w, int u, int v) {
    for (int j = f.size() - 1; j >= w; j--) {
        for (int k = f[j].size() - 1; k >= u; k--) {
            if (f[j - w][k - u] != -inf) {
                f[j][k] = max(f[j][k], f[j - w][k - u] + v);
            }
        }
    }
}
