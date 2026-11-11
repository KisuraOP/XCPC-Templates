/*
add01(f, w); 插入一件重量 w 的物品。
del01(f, w); 删除一件重量 w 的物品。

addall(f, w); 插入一种重量 w、数量不限的物品。
delall(f, w); 删除一种重量 w、数量不限的物品。

count(f, w, c); 插入一种重量 w、至多 c 件的物品，c >= 0。
以上操作均为 O(m)，需要定义 mod。
*/
void add01(vector<int> &f, int w) {
    for (int j = f.size() - 1; j >= w; j--) {
        f[j] = (f[j] + f[j - w]) % mod;
    }
}
void del01(vector<int> &f, int w) {
    for (int j = w; j < f.size(); j++) {
        f[j] = (f[j] - f[j - w] + mod) % mod;
    }
}
void addall(vector<int> &f, int w) {
    for (int j = w; j < f.size(); j++) {
        f[j] = (f[j] + f[j - w]) % mod;
    }
}
void delall(vector<int> &f, int w) {
    for (int j = f.size() - 1; j >= w; j--) {
        f[j] = (f[j] - f[j - w] + mod) % mod;
    }
}
void count(vector<int> &f, int w, int c) {
    auto g = f;
    for (int r = 0; r < w && r < f.size(); r++) {
        int s = 0;
        for (int j = r; j < f.size(); j += w) {
            s = (s + g[j]) % mod;
            if ((j - r) / w > c) {
                s = (s - g[j - (c + 1) * w] + mod) % mod;
            }
            f[j] = s;
        }
    }
}
