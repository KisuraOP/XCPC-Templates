mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
	return rng() % (r - l + 1) + l;
}