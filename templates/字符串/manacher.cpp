/*
auto res = manacher(s);
s 为待处理字符串，0-index。
返回了一个三元组，分别为回文半径数组，最长回文子串的起始位置和长度。

获取方式如下：
vector<int> rad = get<0>(res);
int pos = get<1>(res);
int len = get<2>(res);

多次询问字符串的某个子串是否回文：
auto isr = [&] (int l, int r) {
    return rad[l + r + 1] >= r - l + 1;
};
rad 数组即为上文中的回文半径数组
*/

// 0-index
tuple<vector<int>, int, int> manacher(string s) {
    string t = "#";
    for (auto c : s) {
        t += c;
        t += '#';
    }
    int n = t.size();
    vector<int> r(n);
    for (int i = 0, j = 0; i < n; i++) {
        if (2 * j - i >= 0 && j + r[j] > i) {
            r[i] = min(r[2 * j - i], j + r[j] - i);
        }
        while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]]) {
            r[i] += 1;
        }
        if (i + r[i] > j + r[j]) {
            j = i;
        }
    }
    int pos = max_element(r.begin(), r.end()) - r.begin();
    int ans = r[pos] - 1;
    pos = pos / 2 - ans / 2;
    return {r, pos, ans};
}