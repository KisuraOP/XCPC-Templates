// 依赖 Poly_Mul.cpp、Poly_Div.cpp。
// ---------- 多项式多点求值 O(Mlog^2M) ----------

vector<vector<int>> ptr;
void build_ptr(int p, int l, int r, const vector<int> &A) {
	if (l == r) {
		ptr[p] = {(mod - A[l]) % mod, 1};
		return ;
	}
	int mid = l + r >> 1;
	build_ptr(p << 1, l, mid, A);
	build_ptr(p << 1 | 1, mid + 1, r, A);
	ptr[p] = ptr[p << 1] * ptr[p << 1 | 1];
}
void calc_ptr(vector<int> F, int p, int l, int r, const vector<int> &A, vector<int> &res) {
	if (r - l < 64) {
		for (int i = l; i <= r; i++) {
			res[i] = eval(F, A[i]);
		}
		return ;
	}
	F = F % ptr[p];
	int mid = l + r >> 1;
	calc_ptr(F, p << 1, l, mid, A, res);
	calc_ptr(F, p << 1 | 1, mid + 1, r, A, res);
}
vector<int> multi_eval(const vector<int> &F, const vector<int> &A) {
	if (A.empty()) {
		return {};
	}
	int m = A.size();
	ptr.assign(4 * m, {});
	build_ptr(1, 0, m - 1, A);
	vector<int> res(m);
	calc_ptr(F, 1, 0, m - 1, A, res);
	return res;
}

