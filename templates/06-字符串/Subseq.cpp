/*
Subseq q(s);
预处理 O(nS)，字符为 'a' 到 'a' + S - 1。

q.nxt[p][c]：位置 p 之后字符 'a' + c 的最早出现位置。
若不存在，则返回 0；匹配的初始状态为 0。

q.match(t);
判断 t 是否为 s 的子序列，O(|t|)。
*/
struct Subseq {
    static constexpr int S = 26;
    vector<array<int, S>> nxt;
    Subseq(const string &s) : nxt(s.size()) {
        for (int i = s.size() - 1; i >= 1; i--) {
            nxt[i - 1] = nxt[i];
            nxt[i - 1][s[i] - 'a'] = i;
        }
    }
    bool match(const string &s) {
        int p = 0;
        for (int i = 1; i < s.size(); i++) {
            p = nxt[p][s[i] - 'a'];
            if (!p) {
                return false;
            }
        }
        return true;
    }
};
