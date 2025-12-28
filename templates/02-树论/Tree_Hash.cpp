mt19937_64 rng(time(0));
unsigned int mask = rng();
unsigned int shift(unsigned int x) {
	x ^= mask;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	x ^= mask;
	return x;
}
// hash[x] += shift(hash[y])