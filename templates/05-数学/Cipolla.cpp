/*
求解二次剩余 x^2 \equiv n \pmod {p}
返回全部解，若无解返回空 vector
时间复杂度 O(log p)

Cipolla C(p);
auto ans = C.solve(n);
*/

int qpow(int k, int n, int p) {
	int s = 1;
	for ( ; n; n >>= 1, k = k * k % p) {
		if (n & 1) {
			s = s * k % p;
		}
	}
	return s;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
using P = array<int, 2>;

struct Cipolla {
	int p, w;
	Cipolla(int p_) {
		p = p_;
	}
	vector<int> solve(int n) {
		if (n == 0 || p == 2) {
			return {n};
		}
		if (qpow(n, (p - 1) / 2, p) == p - 1) {
			return {};
		}
		int a = 0;
		while (true) {
			a = rng() % p;
			w = (a * a % p - n + p) % p;
			if (qpow(w, (p - 1) / 2, p) == p - 1) {
				break;
			}
		}
		auto mul = [&] (P x, P y) {
			P res;
			res[0] = (x[0] * y[0] % p + x[1] * y[1] % p * w % p) % p;
			res[1] = (x[0] * y[1] % p + x[1] * y[0] % p) % p;
			return res;
		};
		auto cqpow = [&] (P k, int n) {
			P s = {1, 0};
			for ( ; n; n >>= 1, k = mul(k, k)) {
				if (n & 1) {
					s = mul(s, k);
				}
			}
			return s;
		};
		P res = cqpow({a, 1}, (p + 1) / 2);
		int x1 = res[0], x2 = p - x1;
		if (x1 == x2) {
			return {x1};
		}
		if (x1 > x2) {
			swap(x1, x2);
		}
		return {x1, x2};
	}
};