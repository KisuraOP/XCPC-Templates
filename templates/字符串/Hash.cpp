constexpr int base1 = 991;
constexpr int base2 = 1013;
constexpr int mod1 = 992929453;
constexpr int mod2 = 1008793001;

vector<int> pw1, pw2;
void init(int n) {
	pw1.assign(n + 1, 0);
	pw2.assign(n + 1, 0);
	pw1[0] = 1;
	pw2[0] = 1;
	for (int i = 1; i <= n; i++) {
		pw1[i] = pw1[i - 1] * base1 % mod1;
		pw2[i] = pw2[i - 1] * base2 % mod2;
	}
}
struct H {
	array<int, 2> x;
	int len;
	H() : x({0, 0}), len(0) {}
	H(array<int, 2> _x, int _len) : x(_x), len(_len) {}
	H append(int v) {
		return {
			{ (x[0] * base1 % mod1 + v) % mod1, 
			  (x[1] * base2 % mod2 + v) % mod2 }, 
			  len + 1
		};
	}
};
H get(H &l, H &r) {
	return {
		{ (r.x[0] - l.x[0] * pw1[r.len - l.len] % mod1 + mod1) % mod1, 
		  (r.x[1] - l.x[1] * pw2[r.len - l.len] % mod2 + mod2) % mod2 }, 
		  r.len - l.len
	};
}
bool operator == (H &a, H &b) {
	return a.x == b.x;
}


// 随机模底
bool isprime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
int findPrime(int n) {
    while (!isprime(n)) {
        n++;
    }
    return n;
}
mt19937_64 rng(time(0));
const int P = findPrime(rng() % 900000000 + 100000000);