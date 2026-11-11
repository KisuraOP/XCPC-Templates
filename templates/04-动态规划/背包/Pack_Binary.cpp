/*
依赖 Pack.cpp 的 zero，与单调队列版二选一。

multi(f, w, v, c);
加入至多 c 件重量为 w、价值为 v 的物品。
时间复杂度 O(m log c)。
*/
void multi(vector<int> &f, int w, int v, int c) {
    c = min(c, (int)(f.size() - 1) / w);
    for (int k = 1; c; k *= 2) {
        int t = min(k, c);
        zero(f, t * w, t * v);
        c -= t;
    }
}
