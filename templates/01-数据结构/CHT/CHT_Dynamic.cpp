/*
CHT q;

q.insert({k, b});
插入直线 y = kx + b，均摊 O(log n)。

q.query(x);
查询 max(kx + b)，O(log n)。若未插入直线，则返回 -inf。

k、b、x 为整数，插入和查询顺序任意，不支持删除。
inf 需大于查询坐标和交点横坐标的绝对值。
求最小值时插入 {-k, -b}，将查询结果取负。
*/
struct Line {
    mutable int k, b, p;
    bool operator<(const Line &o) const {
        return k < o.k;
    }
    bool operator<(int x) const {
        return p < x;
    }
};
struct CHT : multiset<Line, less<>> {
    int div(int a, int b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = inf;
            return false;
        }
        if (x->k == y->k) {
            x->p = x->b > y->b ? inf : -inf;
        } else {
            x->p = div(y->b - x->b, x->k - y->k);
        }
        return x->p >= y->p;
    }
    void insert(Line l) {
        auto z = multiset::insert(l), y = z++, x = y;
        while (isect(y, z)) {
            z = erase(z);
        }
        if (x != begin() && isect(--x, y)) {
            isect(x, y = erase(y));
        }
        while ((y = x) != begin() && (--x)->p >= y->p) {
            isect(x, erase(y));
        }
    }
    int query(int x) {
        if (empty()) {
            return -inf;
        }
        auto l = *lower_bound(x);
        return l.k * x + l.b;
    }
};
