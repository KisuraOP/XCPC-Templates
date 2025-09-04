/*
bool ok = func(a, b, c);
ok 判断方程 ax + by = c 有无整数解。
若有解，num_x 存储正整数解的数量，min_x 存储 x 的最小正整数解，max_x 存储 x 的最大正整数解，min_y 存储 y 的最小正整数解，max_y 存储 y 的最大正整数解。
*/
int max_x, max_y, min_x, min_y, num_x;
bool func(int a, int b, int c) {
	auto exgcd = [&](auto self, int a, int b, int &d, int &x, int &y) -> void {
		if (!b) {
			d = a;
			x = 1;
			y = 0;
		} else {
			self(self, b, a % b, d, y, x);
			y -= x * (a / b);
		}
	};
	int d, x, y;
	exgcd(exgcd, a, b, d, x, y);
	if (c % d) {
		return false;
	}
	x = x * c / d;
	y = y * c / d;
	int tx = b / d;
	int ty = a / d;
	int k = ceil((1.0 - x) / tx);
	x += tx * k;
	y -= ty * k;
	if (y <= 0) { // no solution for positive intergers
		min_y = y + ty * ceil((1.0 - y) / ty);
		min_x = x;
		max_y = -1;
		max_x = -1;
	} else {
		num_x = (y - 1) / ty + 1;
		min_x = x;
		max_y = y;
		min_y = (y - 1) % ty + 1;
		max_x = x + (y - 1) / ty * tx;
	}
	return true;
}