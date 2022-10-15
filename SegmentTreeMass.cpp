class SegmentTree {
private:
    vector <int> d, s;
    vector <bool> t;
    int n;

    constexpr static int NEUTRAL = INF;

    static int f(int a, int b) {
        return min(a, b);
    }

    void upd(int i) {
        d[i] = f(d[2 * i], d[2 * i + 1]);
    }

    void upd(int i, int x) {
        t[i] = true;
        d[i] += x;
        s[i] += x;
    }

    void push(int i) {
        if (t[i]) {
            t[i] = false;
            upd(2 * i, s[i]);
            upd(2 * i + 1, s[i]);
            s[i] = 0;
        }
    }

    int get(int l, int r, int ql, int qr, int i) {
        if (l >= qr || ql >= r) {
            return NEUTRAL;
        }
        if (l >= ql && r <= qr) {
            return d[i];
        }
        push(i);
        int m = (l + r) / 2;
        return f(
                get(l, m, ql, qr, 2 * i),
                get(m, r, ql, qr, 2 * i + 1)
                );
    }

    void upd(int l, int r, int ql, int qr, int i, int x) {
        if (l >= qr || ql >= r) {
            return;
        }
        if (l >= ql && r <= qr) {
            return upd(i, x);
        }
        push(i);
        int m = (l + r) / 2;
        upd(l, m, ql, qr, 2 * i, x);
        upd(m, r, ql, qr, 2 * i + 1, x);
        upd(i);
    }

public:
    explicit SegmentTree(const vector <int>& v) {
        n = 1;
        while (n < sz(v)) {
            n <<= 1;
        }
        d.resize(2 * n, NEUTRAL);
        t.resize(2 * n, false);
        s.resize(2 * n, 0);
        for (int i = 0; i < sz(v); ++i) {
            d[i + n] = v[i];
        }
        for (int i = n - 1; i > 0; --i) {
            upd(i);
        }
    }

    int get(int l, int r) {
        return get(0, n, l, r, 1);
    }

    void upd(int l, int r, int x) {
        return upd(0, n, l, r, 1, x);
    }
};
