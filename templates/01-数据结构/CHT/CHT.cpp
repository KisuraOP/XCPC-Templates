/*
CHT q;

q.insert({k, b});
插入直线 y = kx + b，要求 k 非递减，均摊 O(1)。

q.query(x);
查询 max(kx + b)，O(log n)。

q.mono(x);
查询 max(kx + b)，要求各次 mono 的 x 非递减，均摊 O(1)。
可与 insert、query 交替调用。

若未插入直线，两种查询均返回 -inf。
求最小值时插入 {-k, -b}，将查询结果取负；转换后仍须满足单调性。
*/
struct Line {
    int k, b;
    int F(int x) {
        return k * x + b;
    }
};
struct CHT {
    vector<Line> q{{0, -inf}};
    int p = 0;
    void insert(Line x) {
        if (q.size() > 1 && q.back().k == x.k) {
            if (q.back().b >= x.b) {
                return;
            }
            q.pop_back();
        }
        while (q.size() > 2) {
            Line a = q[q.size() - 2], b = q.back();
            if ((a.b - b.b) * (x.k - b.k) < (b.b - x.b) * (b.k - a.k)) {
                break;
            }
            q.pop_back();
        }
        q.push_back(x);
        p = min(p, (int)q.size() - 1);
    }
    int query(int x) {
        int l = 0, r = q.size() - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (q[mid].F(x) <= q[mid + 1].F(x)) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return q[l].F(x);
    }
    int mono(int x) {
        while (p + 1 < q.size() && q[p].F(x) <= q[p + 1].F(x)) {
            p++;
        }
        return q[p].F(x);
    }
};
