int F(int y, int m, int d) {
	if (m == 1 || m == 2) {
		y--;
		m += 12;
	}
	int c = y / 100;
	y %= 100;
	int res = y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1;
	return (res % 7 + 7) % 7;
}

int a[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int isr(int y) {
	return (y % 4 == 0 && y % 100) || (y % 400 == 0);
}