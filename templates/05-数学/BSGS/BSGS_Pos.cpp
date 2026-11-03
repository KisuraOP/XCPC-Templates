// 依赖 BSGS.cpp、BSGS_Ex.cpp。
// 最小正整数解，无解返回 -inf
int BSGS1(int a, int b, int p) {
	int x, y, d;
	exgcd(a, p, d, x, y);
	if (b % d) {
		return -inf;
	}
	int t = exBSGS(a, b / d * x % (p / d), p / d);
	return t < 0 ? -inf : t + 1;
}
