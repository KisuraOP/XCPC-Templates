/*
依赖 Bound_Flow.cpp。

auto [ok, flow] = maxfl(t, s, f);
求 s 到 f 的最大流。若无解则 ok = 0；否则用 t.get(id) 读取方案。
*/
array<int, 2> maxfl(BFlow &t, int s, int f) {
    if (!t.work(s, f)) {
        return {0, 0};
    }
    t.val += t.g.dinic(s, f);
    return {1, t.val};
}
