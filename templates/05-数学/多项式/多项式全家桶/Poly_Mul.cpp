constexpr int mod = 998244353;
constexpr int G = 3; // 原根

constexpr int qpow(int k, int n) {
    int s = 1;
    for ( ; n; n >>= 1, k = k * k % mod) {
        if (n & 1) {
            s = s * k % mod;
        }
    }
    return s;
}

// ---------- 多项式乘法 (NTT) ---------- 

const int Ginv = qpow(G, mod - 2);
vector<int> rt = {0, 1}, irt = {0, 1};

void init_rt(int n) {
    int sz = rt.size();
    if (sz >= n) {
        return;
    }
    while (sz < n) {
        sz <<= 1;
    }
    rt.resize(sz);
    irt.resize(sz);
    for (int k = 2; k < sz; k <<= 1) {
        int z = qpow(G, (mod - 1) / (2 * k));
        int iz = qpow(Ginv, (mod - 1) / (2 * k));
        for (int j = 0; j < k; j += 2) {
            rt[k + j] = rt[(k >> 1) + (j >> 1)];
            rt[k + j + 1] = rt[k + j] * z % mod;
            irt[k + j] = irt[(k >> 1) + (j >> 1)];
            irt[k + j + 1] = irt[k + j] * iz % mod;
        }
    }
}
void dft(vector<int> &a) {
    int n = a.size();
    if (rt.size() < n) {
        init_rt(n);
    }
    for (int k = n >> 1; k > 0; k >>= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            const int* w = &rt[k]; 
            for (int j = 0; j < k; j++) {
                int u = a[i + j];
                int v = a[i + j + k];
                int s = u + v, t = u - v;
                a[i + j] = (s >= mod ? s - mod : s);
                a[i + j + k] = (t < 0 ? t + mod : t) * w[j] % mod;
            }
        }
    }
}
void idft(vector<int> &a) {
    int n = a.size();
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            const int* w = &irt[k];
            for (int j = 0; j < k; j++) {
                int u = a[i + j];
                int v = a[i + j + k] * w[j] % mod;
                int s = u + v, t = u - v;
                a[i + j] = (s >= mod ? s - mod : s);
                a[i + j + k] = (t < 0 ? t + mod : t);
            }
        }
    }
    int inv = qpow(n, mod - 2);
    for (int i = 0; i < n; i++) {
        a[i] = a[i] * inv % mod;
    }
}
vector<int> operator*(vector<int> a, vector<int> b) {
    int sz = 1, n = a.size() + b.size() - 1;
    while (sz < n) {
        sz <<= 1;
    }
    a.resize(sz);
    b.resize(sz);
    dft(a);
    dft(b);
    for (int i = 0; i < sz; i++) {
        a[i] = a[i] * b[i] % mod;
    }
    idft(a);
    a.resize(n);
    return a;
}

