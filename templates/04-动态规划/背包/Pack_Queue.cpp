/*
multi(f, w, v, c);
加入至多 c 件重量为 w、价值为 v 的物品。
时间复杂度 O(m)。
*/
void multi(vector<int> &f, int w, int v, int c) {
    int m = f.size() - 1;
    c = min(c, m / w);
    auto g = f;
    vector<int> q(m + 1);
    for (int r = 0; r < w && r <= m; r++) {
        int l = 0, h = 0;
        for (int j = r; j <= m; j += w) {
            while (l < h && j - q[l] > c * w) {
                l++;
            }
            if (g[j] != -inf) {
                while (l < h && g[q[h - 1]] + (j - q[h - 1]) / w * v <= g[j]) {
                    h--;
                }
                q[h++] = j;
            }
            f[j] = l < h ? g[q[l]] + (j - q[l]) / w * v : -inf;
        }
    }
}
