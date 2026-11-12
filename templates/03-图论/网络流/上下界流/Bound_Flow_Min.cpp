/*
依赖 Bound_Flow.cpp。

auto [ok, flow] = minfl(t, s, f);
求 s 到 f 的最小流。若无解则 ok = 0；否则用 t.get(id) 读取方案。

示例：
BFlow t(2);
t.add(2, 1, 2, 5);
minfl(t, 1, 2) 返回 {1, -5}，maxfl 返回 {1, -2}。
分别求最小、最大值时，各建一个 BFlow 并加入原边。
*/
array<int, 2> minfl(BFlow &t, int s, int f) {
    if (!t.work(s, f)) {
        return {0, 0};
    }
    t.val -= t.g.dinic(f, s);
    return {1, t.val};
}
