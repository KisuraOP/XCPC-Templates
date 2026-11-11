/*
auto sa = suffix(s);
sa[i] 为字典序第 i 小的后缀起点，O(n)。

auto sa = suffix(a, m);
a 为整数序列，取值在 [1, m]，O(n + m)。
若先排序离散化，另计 O(n log n)。与 SA.cpp 选择一份使用。
*/
vector<int> sais(const vector<int> &s, int m) {
    int n = s.size() - 1;
    if (n == 1) {
        return {0, 1};
    }
    vector<int> sa(n + 1), t(n + 1), id(n + 1), c(m + 2), b;
    t[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        t[i] = s[i] < s[i + 1] || (s[i] == s[i + 1] && t[i + 1]);
    }
    for (int i = 1; i <= n; i++) {
        c[s[i] + 1]++;
    }
    for (int i = 1; i <= m + 1; i++) {
        c[i] += c[i - 1];
    }
    auto work = [&] (const vector<int> &a) {
        fill(sa.begin(), sa.end(), 0);
        b = c;
        for (int i = a.size() - 1; i >= 1; i--) {
            sa[b[s[a[i]] + 1]--] = a[i];
        }
        b = c;
        for (int i = 1; i <= n; i++) {
            int v = sa[i] - 1;
            if (v > 0 && !t[v]) {
                sa[++b[s[v]]] = v;
            }
        }
        b = c;
        for (int i = n; i >= 1; i--) {
            int v = sa[i] - 1;
            if (v > 0 && t[v]) {
                sa[b[s[v] + 1]--] = v;
            }
        }
    };
    vector<int> pos(1);
    for (int i = 2; i <= n; i++) {
        if (t[i] && !t[i - 1]) {
            id[i] = pos.size();
            pos.push_back(i);
        }
    }
    work(pos);
    vector<int> a(pos.size());
    for (int i = 1, p = 0, lst = 0; i <= n; i++) {
        int v = sa[i];
        if (!id[v]) {
            continue;
        }
        if (lst) {
            int x = lst, y = v;
            while (s[x] == s[y] && t[x] == t[y]) {
                x++;
                y++;
                if (id[x] || id[y]) {
                    break;
                }
            }
            p += s[x] != s[y] || t[x] != t[y] || !id[x] || !id[y];
        }
        a[id[v]] = p;
        lst = v;
    }
    auto ord = sais(a, pos.size() - 2);
    for (int i = 1; i < ord.size(); i++) {
        ord[i] = pos[ord[i]];
    }
    work(ord);
    return sa;
}
vector<int> suffix(vector<int> s, int m) {
    s.push_back(0);
    auto sa = sais(s, m);
    sa.erase(sa.begin() + 1);
    return sa;
}
vector<int> suffix(const string &s) {
    vector<int> a(s.size());
    for (int i = 1; i < s.size(); i++) {
        a[i] = s[i] + 1;
    }
    return suffix(a, 128);
}
