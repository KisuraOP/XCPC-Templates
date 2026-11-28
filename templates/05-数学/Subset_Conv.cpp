/*
auto h = conv_subset(f, g, n);
n 为元素个数，f、g 的下标为 [0, 2^n) 内的子集，长度均为 2^n。
h[S] = sum_{T subseteq S} f[T] * g[S \ T]。
时间复杂度 O(n^2 2^n)。
*/
constexpr int mod = 998244353;

vector<int> conv_subset(vector<int> f, vector<int> g, int n) {
	int N = 1 << n;
	vector<int> pc(N);
	for (int i = 1; i < N; i++) {
		pc[i] = pc[i >> 1] + (i & 1);
	}
	vector a(n + 1, vector<int>(N)), b(a);
	for (int S = 0; S < N; S++) {
		a[pc[S]][S] = f[S];
		b[pc[S]][S] = g[S];
	}
	for (int k = 0; k <= n; k++) {
		for (int i = 0; i < n; i++) {
			for (int S = 0; S < N; S++) {
				if (S >> i & 1) {
					int T = S ^ (1 << i);
					a[k][S] = (a[k][S] + a[k][T]) % mod;
					b[k][S] = (b[k][S] + b[k][T]) % mod;
				}
			}
		}
	}
	for (int k = n; k >= 0; k--) {
		for (int S = 0; S < N; S++) {
			int s = 0;
			for (int i = 0; i <= k; i++) {
				s = (s + a[i][S] * b[k - i][S]) % mod;
			}
			a[k][S] = s;
		}
	}
	for (int k = 0; k <= n; k++) {
		for (int i = 0; i < n; i++) {
			for (int S = 0; S < N; S++) {
				if (S >> i & 1) {
					a[k][S] = (a[k][S] - a[k][S ^ (1 << i)] + mod) % mod;
				}
			}
		}
	}
	vector<int> h(N);
	for (int S = 0; S < N; S++) {
		h[S] = a[pc[S]][S];
	}
	return h;
}
