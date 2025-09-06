void exgcd(int a, int b, int &d, int &x, int &y) {
	if (!b) {
		d = a;
		x = 1;
		y = 0;
	} else {
		exgcd(b, a % b, d, y, x);
		y -= x * (a / b);
	}
}
int inv(int a, int p) {
	int d, x, y;
	exgcd(a, p, d, x, y);
	return (x % p + p) % p;
} 