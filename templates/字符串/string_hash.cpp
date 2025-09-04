// 常用质数: 10000000000002049，100000000001467，1000000933，1145141，10000799

using ull = unsigned long long;
ull base = 131;
ull mod1 = 212370440130137957, mod2 = 1e9 + 7;

vector<ull> get_hash(string s, ull mod) {
	ull ans = 0;
	vector<ull> h(s.size());
	for (int i = 0; i < s.size(); i++) {
		ans = (ans * base + (ull)s[i]) % mod;
		h[i] = ans;
	}
	return h;
}

void solve() {
	string s;
	cin >> s;
	int n = s.size();
	vector<vector<ull>> h(2);
	h[0] = get_hash(s, mod1);
	h[1] = get_hash(s, mod2);
	vector<array<int, 2>> p;
	p[0] = {1, 1};
	for (int i = 1; i < n; i++) {
		p[i][0] = p[i - 1][0] * base % mod1;
		p[i][1] = p[i - 1][1] * base % mod2;
	}
	auto get = [&] (int l, int r) -> array<ull, 2> {
		return {(h[r][0] - h[l - 1][0] * p[r - l + 1][0] % mod1 + mod1) % mod1,
				(h[r][1] - h[l - 1][1] * p[r - l + 1][1] % mod2 + mod2) % mod2};
	};
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