/*
Du t(s, g, h);
s 为 f 的预处理前缀和，s[0] = 0。
g(x)、h(x) 分别返回辅助函数 g 和 f*g 的前缀和，要求 g(1) = 1。

t.sum(n);
返回 f 在 [1, n] 的和，多次查询可复用同一对象。
*/
template<class G, class H>
struct Du {
	vector<int> s;
	G g;
	H h;
	unordered_map<int, int> mp;
	Du(vector<int> s, G g, H h) : s(move(s)), g(g), h(h) {}
	int sum(int n) {
		if (n < s.size()) {
			return s[n];
		}
		auto it = mp.find(n);
		if (it != mp.end()) {
			return it->second;
		}
		int ans = h(n);
		for (int l = 2, r; l <= n; l = r + 1) {
			r = n / (n / l);
			ans -= (g(r) - g(l - 1)) * sum(n / l);
		}
		return mp[n] = ans;
	}
};
