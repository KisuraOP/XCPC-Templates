// start with p = 1
struct ACTree {
	static constexpr int S = 26;
	struct Node {
		int fail;
		array<int, S> nxt;
		Node() : fail{0}, nxt{} {}
	};
	vector<Node> t;

	ACTree() {
		t.assign(2, Node());
		t[0].nxt.fill(1);
	}
	int newNode() {
		t.emplace_back();
		return t.size() - 1;
	}
	int add(string s) {
		int p = 1;
		for (auto c : s) {
			int x = c - 'a';
			if (t[p].nxt[x] == 0) {
				t[p].nxt[x] = newNode();
			}
			p = t[p].nxt[x];
		}
		return p;
	}
	void work() {
		queue<int> q;
		q.push(1);
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			for (int i = 0; i < S; i++) {
				if (t[x].nxt[i] == 0) {
					t[x].nxt[i] = t[t[x].fail].nxt[i];
				} else {
					t[t[x].nxt[i]].fail = t[t[x].fail].nxt[i];
					q.push(t[x].nxt[i]);
				}
			}
		}
	}
	int next(int p, int x) {
		return t[p].nxt[x];
	}
	int fail(int p) {
		return t[p].fail;
	}
	int size() {
		return t.size();
	}
};