// 依赖 SAM.cpp。
int getLCS(string s, string t) {
    SAM G;
    for (int i = 0, p = 1; i < s.size(); i++) {
        p = G.extend(p, s[i] - 'a');
    }
    int len = 0, res = 0;
    for (int i = 0, p = 1; i < t.size(); i++) {
        int c = t[i] - 'a';
        if (G.next(p, c)) {
            len++;
            p = G.next(p, c);
        } else {
            while (p && G.next(p, c) == 0) {
                p = G.link(p);
            }
            if (p) {
                len = G.len(p) + 1;
                p = G.next(p, c);
            } else {
                len = 0;
                p = 1;
            }
        }
        res = max(res, len);
    }
    return res;
}

