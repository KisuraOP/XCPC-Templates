/*
依赖 Pack.cpp 的 zero，与单调队列版二选一。

multi(f, w, v, c);
加入重量 w、价值 v、至多 c 件的物品，c >= 0。
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
