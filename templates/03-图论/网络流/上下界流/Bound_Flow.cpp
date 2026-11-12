/*
依赖 maxFlow_Ext.cpp。

BFlow t(n);
int id = t.add(x, y, l, r);
加入流量下界为 l、上界为 r 的有向边，返回原边编号。

bool ok = t.work();
求无源汇可行流，若无解则返回 false。

int f = t.get(id);
求解成功后，读取原边的实际流量。

加完边后，调用一次 work、maxfl 或 minfl。
*/
struct BFlow {
    int n, val = 0;
    Dinic g;
    vector<int> d, lo, id;
    BFlow(int n) : n(n), g(n + 2), d(n + 1), lo(1), id(1) {}
    int add(int x, int y, int l, int r) {
        id.push_back(g.add(x, y, r - l));
        lo.push_back(l);
        d[x] -= l;
        d[y] += l;
        return id.size() - 1;
    }
    int get(int i) {
        return lo[i] + g.e[id[i] ^ 1].cap;
    }
    bool work(int s = 0, int t = 0) {
        int p = g.e.size(), sum = 0;
        if (s) {
            g.add(t, s, inf);
            g.add(s, t, inf);
        }
        for (int i = 1; i <= n; i++) {
            if (d[i] > 0) {
                g.add(n + 1, i, d[i]);
                sum += d[i];
            } else if (d[i] < 0) {
                g.add(i, n + 2, -d[i]);
            }
        }
        bool ok = g.dinic(n + 1, n + 2) == sum;
        if (s) {
            val = g.e[p + 1].cap - g.e[p + 3].cap;
        }
        for (int i = p; i < g.e.size(); i++) {
            g.e[i].cap = 0;
        }
        return ok;
    }
};
