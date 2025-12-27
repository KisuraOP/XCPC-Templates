/*
分为不可删除版本和可删除版本。

时间复杂度均为 O(log n)。

因为后者需要用 `std::multiset` 代替 `std::priority_queue`，常数略大。

Node t;

t.insert(x);
插入数 x。

t.erase(x);
删除数 x。

int res = t.get();
获取当前中位数。
中位数定义为 1-index 下排序后的第 "n / 2 下取整" 个数。
*/

struct Node {
	priority_queue<int, vector<int>, greater<int>> s1;
	priority_queue<int> s2;
	int n = 0;
	void update() {
		if (s1.size() > s2.size() + 1) {
			s2.push(s1.top());
			s1.pop();
		}
		if (s2.size() > s1.size()) {
			s1.push(s2.top());
			s2.pop();
		}
	}
	void insert(int x) {
		n++;
		if (s1.empty() || x >= s1.top()) {
			s1.push(x);
		} else {
			s2.push(x);
		}
		update();
	}
	int get() {
		if (n % 2 == 0 && !s2.empty()) {
			return s2.top();
		}
		return s1.top();
	}
};

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
		if (s2.count(x)) {
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