vector<int> suffArray(string s) {
    s += '#';
    int lg = 0;
    while ((1 << lg) < sz(s)) ++lg;
    vector<int> p(s.size()), c(s.size());
    {
        vector<pair<char, int>> p1(s.size());
        for (int i = 0; i < sz(s); ++i) {
            p1[i] = {s[i], i};
        }
        sort(all(p1));
        for (int i = 0; i < sz(s); ++i) {
            p[i] = p1[i].second;
        }
        vector<int> cl(256, 0);
        int cnt = 0;
        for (int i = 0; i < p1.size(); ++i) {
            if (i > 0 && p1[i].first != p1[i - 1].first) {
                ++cnt;
            }
            cl[p1[i].first] = cnt;
        }
        for (int i = 0; i < s.size(); ++i) {
            c[i] = cl[s[i]];
        }
    }
    for (int k = 0; k < lg; ++k) {
        vector<int> p1(p.size());
        for (int i = 0; i < sz(p1); ++i) {
            p1[i] = (p[i] - (1 << k) + 2 * (int) s.size()) % (int) s.size();
        }
        vector<int> cnt(s.size(), 0);
        for (long long i: c) {
            ++cnt[i];
        }
        vector<int> pr(cnt.size() + 1, 0);
        for (int i = 1; i < pr.size(); ++i) {
            pr[i] = pr[i - 1] + cnt[i - 1];
        }
        for (auto x: p1) {
            p[pr[c[x]]++] = x;
        }
        vector<int> c1(s.size(), 0);
        for (int i = 1; i < sz(s); ++i) {
            c1[i] = c1[i - 1] + (pair<int, int>({c[p[i - 1]], c[(p[i - 1] + (1 << k)) % s.size()]}) !=
                                 pair<int, int>({c[p[i]], c[(p[i] + (1 << k)) % s.size()]}));
        }
        for (int i = 0; i < sz(s); ++i) {
            c[p[i]] = c1[i];
        }
    }
    return vector<int>(p.begin() + 1, p.end());
}

vector<int> LCP(const string &s, const vector<int> &p) {
    const int n = sz(s);
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        c[p[i]] = i;
    }
    vector<int> lcp(n - 1, 0);
    for (int i = 0; i < n; ++i) {
        if (c[i] == n - 1) continue;
        while (max(i, p[c[i] + 1]) + lcp[c[i]] < n &&
               s[i + lcp[c[i]]] == s[p[c[i] + 1] + lcp[c[i]]]) {
            ++lcp[c[i]];
        }
        if (i + 1 < n && c[i + 1] < n - 1) {
            lcp[c[i + 1]] = max(0ll, lcp[c[i]] - 1);
        }
    }
    return lcp;
}
