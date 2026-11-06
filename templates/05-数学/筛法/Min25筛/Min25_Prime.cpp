/*
依赖 Min25.cpp。

prime2(n);
返回不超过 n 的所有质数的平方和。
*/
int prime2(int n) {
	Min25 t(n);
	return t.prime([](int x) {
		return x * x;
	}, [](int x) {
		return x * (x + 1) * (2 * x + 1) / 6;
	})[1];
}
