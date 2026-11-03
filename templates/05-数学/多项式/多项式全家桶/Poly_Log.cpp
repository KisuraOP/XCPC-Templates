#include <cassert>
// 依赖 Poly_Mul.cpp、Poly_Base.cpp、Poly_Inv.cpp。
// ---------- 多项式对数函数 O(NlogN) ----------

// 要求: a[0] == 1
vector<int> poly_log(vector<int> a, int n) {
	assert(!a.empty() && a[0] == 1);
	a.resize(n);
	auto res = poly_deriv(a) * poly_inv(a, n);
	res.resize(n);
	res = poly_integral(res);
	res.resize(n);
	return res;
}

