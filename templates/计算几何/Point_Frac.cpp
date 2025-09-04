int mygcd(int a, int b) { 
	return b == 0 ? a : mygcd(b, a % b); 
}
struct Frac {
	int num, den; 
	void work() {
		if (den < 0) { num = -num; den = -den;}
		if (num == 0) { den = 1; return;}
		int d;
		if (num < 0) { d = mygcd(-num, den);} 
		else { d = mygcd(num, den);}
		num /= d; den /= d;
	}
	Frac() : num(0), den(1) {}
	Frac(int x) : num(x), den(1) {}
	Frac(int x, int y) : num(x), den(y) { work();}
	Frac operator - () const { return Frac(-num, den);}
	Frac& operator += (const Frac &oth) { num = num * oth.den + oth.num * den; den = den * oth.den; work(); return *this;}
	Frac& operator -= (const Frac &oth) { num = num * oth.den - oth.num * den; den = den * oth.den; work(); return *this;}
	Frac& operator *= (const Frac &oth) { num *= oth.num; den *= oth.den; work(); return *this;}
	Frac& operator /= (const Frac &oth) { assert(oth.num != 0); num *= oth.den; den *= oth.num; work(); return *this;}
	explicit operator double() const { return static_cast<double>(num) / den;}
};
Frac operator + (Frac lhs, const Frac &rhs) { return lhs += rhs;}
Frac operator - (Frac lhs, const Frac &rhs) { return lhs -= rhs;}
Frac operator * (Frac lhs, const Frac &rhs) { return lhs *= rhs;}
Frac operator / (Frac lhs, const Frac &rhs) { return lhs /= rhs;}
bool operator == (const Frac &lhs, const Frac &rhs) { return lhs.num == rhs.num && lhs.den == rhs.den;}
bool operator != (const Frac &lhs, const Frac &rhs) { return !(lhs == rhs);}
bool operator < (const Frac &lhs, const Frac &rhs) { return lhs.num * rhs.den < rhs.num * lhs.den;}
bool operator > (const Frac &lhs, const Frac &rhs) { return rhs < lhs;}
bool operator <= (const Frac &lhs, const Frac &rhs) { return !(lhs > rhs);}
bool operator >= (const Frac &lhs, const Frac &rhs) { return !(lhs < rhs);}
std::ostream& operator<<(ostream &os, const Frac &f) {
	os << f.num;
	if (f.den != 1) {
		os << '/' << f.den;
	}
	return os;
}

struct P {
	Frac x, y;
	P() : x(0, 1), y(0, 1) {}
	P(int x, int y) : x(x, 1), y(y, 1) {}
	P(Frac _x, Frac _y) : x(_x), y(_y) {}
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
	friend P operator * (const P &a, const Frac &b) {
		return P(a.x * b, a.y * b);
	}
	friend P operator * (const Frac &a, const P &b) {
		return P(a * b.x, a * b.y);
	}
	bool operator < (const P &oth) const {
		if (x != oth.x) {
			return x < oth.x;
		}
		return y < oth.y;
	}
};
bool operator == (const P &lhs, const P &rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}