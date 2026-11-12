/*
依赖 Fraction.cpp，以下成员按需放入 F 内。
*/
F& operator += (F b) {
    return *this = *this + b;
}
F& operator -= (F b) {
    return *this = *this - b;
}
F& operator *= (F b) {
    return *this = *this * b;
}
F& operator /= (F b) {
    return *this = *this / b;
}
friend bool operator != (F a, F b) {
    return !(a == b);
}
friend bool operator > (F a, F b) {
    return b < a;
}
friend bool operator <= (F a, F b) {
    return !(b < a);
}
friend bool operator >= (F a, F b) {
    return !(a < b);
}
explicit operator double() const {
    return (double)p / q;
}
friend ostream& operator << (ostream &os, const F &a) {
    os << a.p;
    if (a.q != 1) {
        os << '/' << a.q;
    }
    return os;
}
