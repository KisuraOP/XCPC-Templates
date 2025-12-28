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
ostream& operator<<(ostream &os, const Frac &f) {
	os << f.num;
	if (f.den != 1) {
		os << '/' << f.den;
	}
	return os;
}