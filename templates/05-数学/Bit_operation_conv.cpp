/*
时间复杂度 O(N\log N)，其中 N = 2^n
*/

constexpr int mod = 998244353;
int qpow(int k, int n) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % mod) {
		if (n & 1) s = s * k % mod;
	}
	return s;
}

void conv_OR(vector<int> &f, int v) {
    int N = f.size();
    for (int o = 2, k = 1; o <= N; o <<= 1, k <<= 1) {
        for (int i = 0; i < N; i += o) {
            for (int j = 0; j < k; j++) {
                f[i + j + k] = (f[i + j + k] + f[i + j] * v + mod) % mod;
            }
        }
    }
}
vector<int> conv_OR(vector<int> f, vector<int> g) {
    conv_OR(f, 1);
    conv_OR(g, 1);
    for (int i = 0; i < f.size(); i++) {
        f[i] = f[i] * g[i] % mod;
    }
    conv_OR(f, -1);
    return f;
}

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

void FWT_XOR(vector<int> &f, int v) {
	int N = f.size();
	for (int o = 2, k = 1; o <= N; o <<= 1, k <<= 1) {
		for (int i = 0; i < N; i += o) {
			for (int j = 0; j < k; j++) {
				int x = f[i + j], y = f[i + j + k];
				f[i + j] = (x + y) % mod;
				f[i + j + k] = (x - y + mod) % mod;
			}
		}
	}
	if (v) {
		int invN = qpow(N, mod - 2);
		for (int &x : f) {
			x = x * invN % mod;
		}
	}
}
vector<int> conv_XOR(vector<int> f, vector<int> g) {
	FWT_XOR(f, 0);
	FWT_XOR(g, 0);
	for (int i = 0; i < f.size(); i++) {
		f[i] = f[i] * g[i] % mod;
	}
	FWT_XOR(f, 1);
	return f;
}