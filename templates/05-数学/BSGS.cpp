unordered_map<int, int> hs;

void exgcd(int a, int b, int &d, int &x, int &y) {
	if (!b) {
		d = a;
		x = 1;
		y = 0;
	} else {
		exgcd(b, a%b, d, y, x);
		y -= x * (a / b);
	}
}

int BSGS(int a, int b, int p) {
	if (1 % p == b % p) {
		return 0;
	}
	int k = sqrtl(p) + 1;
	hs.clear();
	for (int i = 0, r = b % p; i < k; i++) {
		hs[r] = i;
		r = r * a % p;
	}
	int res = 1;
	for (int i = 1; i <= k; i++) {
		res = res * a % p;
	}
	for (int i = 1, j = res; i <= k; i++) {
		if(hs.count(j)) {
			return k * i - hs[j];
		}
		j = j * res % p;
	}
	return -inf;
}

int exBSGS(int a, int b, int p) {
	b = (b % p + p) % p;
	if (1 % p == b % p) {
		return 0;
	}
	int x, y, d;
	exgcd(a, p, d, x, y);
	if (d > 1) {
		if (b % d) {
			return -inf;
		}
		int tmp;
		exgcd(a / d, p / d, tmp, x, y);
		return exBSGS(a, b / d * x % (p / d), p / d) + 1;
	}
	return BSGS(a, b, p);
}