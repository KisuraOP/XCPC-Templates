/*
依赖 Treap_Seq.cpp。

move(t, l, r, k);
将 [l, r] 剪下，插到剩余序列的第 k 个元素后。
k = 0 时插到开头。

时间复杂度为期望 O(log n)，与区间长度无关。

示例：
TreapSeq t(5);
t.build({0, 1, 2, 3, 4, 5});
move(t, 2, 4, 0); // 2, 3, 4, 1, 5
t.flip(1, 3); // 4, 3, 2, 1, 5
t.add(2, 4, 10); // 4, 13, 12, 11, 5
cout << t.ask(1, 4); // 40
*/
void move(TreapSeq &t, int l, int r, int k) {
	int x, y, z, p, q;
	t.split(t.rt, r, y, z);
	t.split(y, l - 1, x, y);
	x = t.merge(x, z);
	t.split(x, k, p, q);
	t.rt = t.merge(t.merge(p, y), q);
}
