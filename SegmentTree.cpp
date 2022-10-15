template <typename T = int>
class SegmentTree {
private:
    vector <T> d;
    int n;

    static T f(T a, T b) {
        return max(a, b);
    }

    void upd(int i) {
        d[i] = f(d[2 * i], d[2 * i + 1]);
    }

public:
    constexpr const static T NEUTRAL = make_pair((int) -1e9, (int) -1e9);
    explicit SegmentTree(const vector <T>& v) {
        n = 1;
        while (n < sz(v)) {
            n <<= 1;
        }
        d.resize(2 * n, NEUTRAL);
        for (int i = 0; i < sz(v); ++i) {
            d[i + n] = v[i];
        }
        for (int i = n - 1; i > 0; --i) {
            upd(i);
        }
    }

    T get(int l, int r) {
        T res = NEUTRAL;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res = f(res, d[l++]);
            }
            if (r & 1) {
                res = f(res, d[--r]);
            }
        }
        return res;
    }

    void upd(int i, T x) {
        d[i += n] = x;
        while (i >>= 1) {
            upd(i);
        }
    }
};
