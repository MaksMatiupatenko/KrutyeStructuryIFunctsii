template <typename T>
struct Line {
    T k = 0, b = -INF;

    Line() = default;

    Line(T k, T b) : k(k), b(b) {}

    T operator()(int a) const {
        return k * a + b;
    }
};

template <typename T>
double intersection(Line<T> a, Line<T> b) {
    return ((double) (b.b - a.b)) / (double) (a.k - b.k);
}

template <typename T>
class LiChao {
    using Line_ = Line<T>;

    struct Node {
        Line_ a{};
        Node *l{}, *r{};
    };

    Node *root;
    int n;
    int N;

    static void finishNode(Node *t) {
        if (!t->l) {
            t->l = new Node();
        }
        if (!t->r) {
            t->r = new Node();
        }
    }

    int MN;

    void add(Line_ a, int l, int r, Node *t) {
        finishNode(t);
        int m = (l + r) / 2 - MN;
        l -= MN, r -= MN;
        int ll = (t->a(l) <= a(l));
        int rr = (t->a(r) <= a(r));
        if (ll && rr) {
            t->a = a;
            return;
        }
        if (t->a(l) >= a(l) && t->a(r) >= a(r)) {
            return;
        }
        auto p = intersection(a, t->a);
        if (p > (double) m) {
            if (ll) {
                swap(a, t->a);
            }
            return add(a, m + 1 + MN, r + MN, t->r);
        } else {
            if (rr) {
                swap(a, t->a);
            }
            return add(a, l + MN, m + MN, t->l);
        }
    }

    T get(int a, int l, int r, Node *t) {
        int m = (l + r) / 2 - MN;
        l -= MN, r -= MN;
        if (a >= r || a < l) {
            return -INF;
        }
        if (l == r - 1) {
            return t->a(a - MN);
        }
        finishNode(t);
        T curr = -INF;
        if (l <= a && a < r) {
            curr = t->a(a);
        }
        return max({curr, get(a, l + MN, m + MN, t->l), get(a, m + MN, r + MN, t->r)});
    }

public:
    explicit LiChao(int l = 0, int r = 4e12l) {
        MN = -l;
        N = r - l + 10;
        n = 1;
        while (n < N) {
            n *= 2;
        }
        root = new Node();
    }

    void add(Line_ a) {
        return add(a, 0, n - 1, root);
    }

    T get(T a) {
        return get(a, 0, n, root);
    }
};
