mt19937_64 rng(time(0));

using ull = unsigned long long;

ull mask = rng();
ull shift(ull x) {
	x ^= mask;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	x ^= mask;
	return x;
}
// hash[x] += shift(hash[y])


vector<ull> f(n + 1);
auto dfs1 = [&] (auto self, int x, int fa) -> void {
	f[x] = 1;
	for (auto y : adj[x]) {
		if (y != fa) {
			self(self, y, x);
			f[x] += shift(f[y]);
		}
	}
};
dfs1(dfs1, 1, 0);


