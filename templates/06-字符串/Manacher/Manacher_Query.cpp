// 依赖 Manacher.cpp。
// rad 为 get<0>(manacher(s))，区间下标从 0 开始。
auto isr = [&] (int l, int r) {
    return rad[l + r + 1] >= r - l + 1;
};
