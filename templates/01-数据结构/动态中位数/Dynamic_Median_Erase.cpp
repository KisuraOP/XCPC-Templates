/*
Node t;

t.insert(x);
插入数 x。

t.erase(x);
删除数 x。

int res = t.get();
获取当前中位数。
中位数定义为 1-index 下排序后的第 "(n + 1) / 2 下取整" 个数。
*/

struct Node {
	multiset<int> s1;
	multiset<int, greater<int>> s2;
	int n = 0;
	void update() {
		if (s1.size() > s2.size() + 1) {
			s2.insert(*s1.begin());
			s1.extract(s1.begin());
		}
		if (s2.size() > s1.size()) {
			s1.insert(*s2.begin());
			s2.extract(s2.begin());
		}
	}
	void insert(int x) {
		n++;
		if (s1.empty() || x >= *s1.begin()) {
			s1.insert(x);
		} else {
			s2.insert(x);
		}
		update();
	}
	void erase(int x) {
		n--;
		if (s2.find(x) != s2.end()) {
			s2.extract(x);
		} else {
			s1.extract(x);
		}
		update();
	}
	int get() {
		if (n % 2 == 0 && s2.size()) {
			return *s2.begin();
		}
		return *s1.begin();
	}
};
