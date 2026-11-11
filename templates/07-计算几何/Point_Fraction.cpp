/*
依赖 ../08-杂项/分数类/Fraction.cpp。

P a(F(1, 2), F(1, 3));
支持加减、数乘和 ==，< 按 (x, y) 字典序比较。
*/
struct P {
	F x, y;
	P() : x(0, 1), y(0, 1) {}
	P(int x, int y) : x(x, 1), y(y, 1) {}
	P(F _x, F _y) : x(_x), y(_y) {}
	friend P operator + (const P &a, const P &b) {
		return P(a.x + b.x, a.y + b.y);
	}
	friend P operator - (const P &a, const P &b) {
		return P(a.x - b.x, a.y - b.y);
	}
	friend P operator * (const P &a, const int &b) {
		return P(a.x * b, a.y * b);
	}
	friend P operator * (const int &a, const P &b) {
		return P(a * b.x, a * b.y);
	}
	friend P operator * (const P &a, const F &b) {
		return P(a.x * b, a.y * b);
	}
	friend P operator * (const F &a, const P &b) {
		return P(a * b.x, a * b.y);
	}
	bool operator < (const P &oth) const {
		if (!(x == oth.x)) {
			return x < oth.x;
		}
		return y < oth.y;
	}
};
bool operator == (const P &lhs, const P &rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}