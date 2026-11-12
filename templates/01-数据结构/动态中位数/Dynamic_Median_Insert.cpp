/*
Node t;

t.insert(x);
插入数 x。

int res = t.get();
返回排序后第 (n + 1) / 2 个数，除法向下取整。
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

