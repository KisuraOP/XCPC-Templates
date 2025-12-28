auto id = [&] (int x, int y) {
	if (x == 0) {
		return S;
	} 
	if (x == n) {
		return T;
	}
	return (x - 1) * (m - 1) + y;
};
for (int i = 1; i <= n; i++) {
	for (int j = 1; j < m; j++) {
		int x = id(i - 1, j);
		int y = id(i, j);
        // x -> y
	}
}	
for (int i = 1; i < n; i++) {
	for (int j = 1; j <= m; j++) {
		if (j == 1 || j == m) {
			continue;
		}
		int x = id(i, j - 1);
		int y = id(i, j);
        // x -> y
	}
}