// 依赖 BSGS.cpp。
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

