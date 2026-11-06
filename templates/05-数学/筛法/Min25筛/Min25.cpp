/*
Min25 t(n);
v 存储 n/i（1 <= i <= n）的不同取值，按降序排列。
id(x) 返回 x 在 v 中的下标。

auto a = t.prime(g, s);
g 为完全积性函数，g(1) = 1，s(x) 返回 g 在 [1, x] 的和。
返回 a[i] = sum_{p <= v[i]} g(p)，p 为质数。

t.sum(a, calc);
a[i] 为目标积性函数 f 在质数 p <= v[i] 上的和，可由多次 prime 的结果组合。
calc(p, k, q, v) 返回 f(p^k)，q = p^k，v = f(p^(k-1))。
返回 f 在 [1, n] 的和，f(1) = 1。
*/
struct Min25 {
	int n;
	vector<int> v{0}, pri;
	Min25(int n) : n(n) {
		for (int l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			v.push_back(n / l);
		}
		int m = v.size() / 2;
		vector<bool> vis(m + 1);
		for (int i = 2; i <= m; i++) {
			if (!vis[i]) {
				pri.push_back(i);
				for (int j = i * i; j <= m; j += i) {
					vis[j] = true;
				}
			}
		}
	}
	int id(int x) {
		return x <= v.size() / 2 ? v.size() - x : n / x;
	}
	template<class F, class G>
	vector<int> prime(F f, G g) {
		vector<int> s(v.size());
		for (int i = 1; i < v.size(); i++) {
			s[i] = g(v[i]) - 1;
		}
		for (int p : pri) {
			int x = f(p), y = s[id(p - 1)];
			for (int i = 1; i < v.size() && p * p <= v[i]; i++) {
				s[i] -= x * (s[id(v[i] / p)] - y);
			}
		}
		return s;
	}
	template<class F>
	int sum(vector<int> s, F calc) {
		for (int j = pri.size() - 1; j >= 0; j--) {
			int p = pri[j], sp = s[id(p)], fp = calc(p, 1, p, 1);
			for (int i = 1; i < v.size() && p * p <= v[i]; i++) {
				int x = v[i];
				for (int q = p, k = 1, val = fp; q <= x / p; q *= p, k++) {
					int nxt = calc(p, k + 1, q * p, val);
					s[i] += val * (s[id(x / q)] - sp) + nxt;
					val = nxt;
				}
			}
		}
		return s[1] + 1;
	}
};
