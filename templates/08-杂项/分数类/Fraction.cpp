/*
F a(x, y);
表示 x/y，要求 y != 0；自动约分，分母为正。

支持四则运算、取负、< 和 ==，以及两侧整数混合运算。
除法要求除数非零。
*/
int mygcd(int a, int b) {
    return b == 0 ? a : mygcd(b, a % b);
}
struct F {
    int p, q;
    F(int x = 0, int y = 1) {
        int d = mygcd(x, y);
        if ((d < 0) != (y < 0)) {
            d = -d;
        }
        p = x / d;
        q = y / d;
    }
    F operator - () const {
        return F(-p, q);
    }
    friend F operator + (F a, F b) {
        return F(a.p * b.q + b.p * a.q, a.q * b.q);
    }
    friend F operator - (F a, F b) {
        return F(a.p * b.q - b.p * a.q, a.q * b.q);
    }
    friend F operator * (F a, F b) {
        return F(a.p * b.p, a.q * b.q);
    }
    friend F operator / (F a, F b) {
        return F(a.p * b.q, a.q * b.p);
    }
    friend bool operator < (F a, F b) {
        return a.p * b.q < b.p * a.q;
    }
    friend bool operator == (F a, F b) {
        return a.p == b.p && a.q == b.q;
    }
};
