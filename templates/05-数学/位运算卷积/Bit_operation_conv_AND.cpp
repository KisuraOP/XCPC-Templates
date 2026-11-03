/*
时间复杂度 O(N\log N)，其中 N = 2^n
*/

constexpr int mod = 998244353;

void conv_AND(vector<int> &f, int v) {
    int N = f.size();
    for (int o = 2, k = 1; o <= N; o <<= 1, k <<= 1) {
        for (int i = 0; i < N; i += o) {
            for (int j = 0; j < k; j++) {
                f[i + j] = (f[i + j] + f[i + j + k] * v + mod) % mod;
            }
        }
    }
}
vector<int> conv_AND(vector<int> f, vector<int> g) {
    conv_AND(f, 1);
    conv_AND(g, 1);
    for (int i = 0; i < f.size(); i++) {
        f[i] = f[i] * g[i] % mod;
    }
    conv_AND(f, -1);
    return f;
}

