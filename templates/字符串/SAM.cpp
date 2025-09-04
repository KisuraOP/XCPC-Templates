// start with p = 1
struct SAM {
    static constexpr int S = 26;
    struct Node {
        int len, link;
        array<int, S> next;
        Node() : len{}, link{}, next{} {}
    };
    vector<Node> t;
    SAM() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    } 
    int next(int p, int x) {
        return t[p].next[x];
    }  
    int link(int p) {
        return t[p].link;
    }    
    int len(int p) {
        return t[p].len;
    }
    int size() {
        return t.size();
    }
};

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
