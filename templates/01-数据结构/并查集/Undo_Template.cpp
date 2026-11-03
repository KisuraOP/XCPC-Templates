// 万用撤销模板
vector<pair<int *, int>> stk;
auto doit = [&] (int &x, int y) {
	stk.push_back({&x, x});
	x = y;
};	
auto roll = [&] (int t) {
	while (stk.size() > t) {
		auto [x, y] = stk.back();
		stk.pop_back();
		*x = y;
	}
};

