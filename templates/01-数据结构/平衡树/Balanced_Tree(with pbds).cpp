#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds; 
struct node {
	int cnt;
	tree<pair<int, int>, null_type, less<pair<int, int>>,  
		 rb_tree_tag, tree_order_statistics_node_update> t; 
	node() : cnt(0) {}

	// 添加一个值为 x 的元素
	void insert(int x) {
		t.insert({x, ++cnt});
	}

	// 删除一个值为 x 的元素
	void erase(int x) {
		t.erase(t.lower_bound({x, 1}));
	}

	// 严格比 x 小的数的个数
	int select(int x) {
		return t.order_of_key({x, 1});
	}

	// 第 k 小的数
	int kth(int k) {
		return t.find_by_order(k - 1)->first;
	}

	// 最大的严格小于 x 的数
	int getpre(int x) {
		return (--t.lower_bound({x, 1}))->first;
	}

	// 最小的严格大于 x 的数
	int getnxt(int x) {
		return t.upper_bound({x, inf})->first;
	}
};