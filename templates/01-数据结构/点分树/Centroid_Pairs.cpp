/*
依赖 Centroid.cpp。

pairs(t, k);
求距离不超过 k 的无序点对数，两个端点满足 u < v。
加完边后直接调用 pairs，不要先调用 t.build。

时间复杂度 O(n log^2 n)。
*/
int pairs(Centroid &t, int k) {
	auto calc = [&](vector<int> &a) {
		sort(a.begin(), a.end());
		int l = 0, r = a.size() - 1, res = 0;
		while (l < r) {
			if (a[l] + a[r] <= k) {
				res += r - l;
				l++;
			} else {
				r--;
			}
		}
		return res;
	};
	int ans = 0;
	t.build([&](int x, int p) {
		vector<int> a{0};
		for (auto [y, w] : t.adj[x]) {
			if (!t.del[y]) {
				vector<int> b;
				t.walk(y, x, w, [&](int z, int d) {
					b.push_back(d);
				});
				ans -= calc(b);
				a.insert(a.end(), b.begin(), b.end());
			}
		}
		ans += calc(a);
	});
	return ans;
}
