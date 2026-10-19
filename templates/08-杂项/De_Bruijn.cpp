// 生成 de_bruijn 序列 B(k, n)
// 字符集为 {0, 1, ..., k - 1}, 长度为 k^n
// 每个长为 n 的 k 进制串恰好在 B(k, n) 中作为子串出现一次 (首尾视作相连)
// 时间复杂度线性, 即 O(k^n)
vector<int> de_bruijn(int k, int n) {
	if (k == 1) return {0};
	vector<int> res;
	vector<int> a(n + 1);
	auto dfs = [&] (auto self, int t, int p) -> void {
		if (t > n) {
			if (n % p == 0) {
				for (int i = 1; i <= p; i++) {
					res.push_back(a[i]);
				}
			}
		} else {
			a[t] = a[t - p];
			self(self, t + 1, p);
			for (int j = a[t - p] + 1; j < k; j++) {
				a[t] = j;
				self(self, t + 1, t);
			}
		}
	};
	dfs(dfs, 1, 1);
	return res;
}
