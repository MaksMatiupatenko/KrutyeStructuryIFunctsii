string reversed(string s) {
    reverse(all(s));
    return s;
}

const int X = 1e9;
const int SZ = 9;

class Polynom : public vector<int> {
private:
    Polynom slowMultiplication(Polynom b) {
        Polynom ans((int) this->size() + sz(b) + 1);
        for (int i = 0; i < (int) this->size(); ++i) {
            for (int j = 0; j < sz(b); ++j) {
                auto t = this->data()[i] * b[j] + ans[i + j];
                if (t >= X) {
                    ans[i + j + 1] += t / X;
                }
                ans[i + j] = t % X;
            }
        }
        return ans + getPolynom("0");
    };

public:
    static Polynom getPolynom(string s) {
        Polynom ans;
        reverse(all(s));
        for (int i = 0; i < sz(s); i += SZ) {
            if (i + SZ <= sz(s)) {
                ans.push_back(stoi(reversed(s.substr(i, SZ))));
            } else {
                ans.push_back(stoi(reversed(s.substr(i))));
            }
        }
        return ans;
    }

    explicit Polynom(int n = 0) : vector<int>(n) {}

    friend Polynom operator+(Polynom a, Polynom b) {
        while (sz(a) < sz(b)) {
            a.push_back(0);
        }
        while (sz(b) < sz(a)) {
            b.push_back(0);
        }
        bool f = false;
        Polynom ans(sz(a));
        for (int i = 0; i < sz(a); ++i) {
            int t = a[i] + b[i] + f;
            f = false;
            if (t / X) {
                f = true;
                t %= X;
            }
            ans[i] = t;
        }
        if (f) {
            ans.push_back(1);
        }
        return ans;
    }

    friend Polynom operator-(Polynom a, Polynom b) {
        int m = max(sz(a), sz(b));
        a.resize(m);
        b.resize(m);
        Polynom ans(sz(a));
        bool f = false;
        for (int i = 0; i < sz(a); ++i) {
            int t = a[i] - b[i] - f;
            f = false;
            if (t < 0) {
                t += X;
                f = true;
            }
            ans[i] = t;
        }
        return ans;
    }

    friend Polynom operator*(Polynom a, Polynom b) {
        if (sz(a) <= 64 || sz(b) <= 64) {
            return a.slowMultiplication(b);
        }
        int m = max(sz(a), sz(b));
        m += m % 2;
        a.resize(m);
        b.resize(m);
        Polynom p, q, r, s;
        int n = sz(a);
        for (int i = 0; i < n / 2; ++i) {
            q.push_back(a[i]);
            s.push_back(b[i]);
        }
        for (int i = n / 2; i < n; ++i) {
            p.push_back(a[i]);
            r.push_back(b[i]);
        }
        Polynom pr = p * r, qs = q * s;
        Polynom qrPLUSps = (p + q) * (r + s) - pr - qs;
        vector<int> st(n / 2, 0);
        qrPLUSps.insert(qrPLUSps.begin(), all(st));
        st.resize(n);
        pr.insert(pr.begin(), all(st));
        Polynom ans = pr + qrPLUSps + qs;
        return ans;
    }

    static string to_string(Polynom p) {
        string ans;
        for (int i = sz(p) - 1; i >= 0; --i) {
            string s = std::to_string(p[i]);
            vector<char> t(max((int) 0, SZ - sz(s)), '0');
            s.insert(s.begin(), all(t));
            ans += s;
        }
        reverse(all(ans));
        while (sz(ans) > 1 && ans.back() == '0') {
            ans.pop_back();
        }
        reverse(all(ans));
        return ans;
    }
};


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    cin >> a >> b;
    bool negative = (count(all(a), '0') != sz(a) && count(all(b), '0') != sz(b)) && ((a[0] == '-') ^ (b[0] == '-'));
    if (a[0] == '-') {
        a.erase(a.begin());
    }
    if (b[0] == '-') {
        b.erase(b.begin());
    }
    auto p = Polynom::getPolynom(a) * Polynom::getPolynom(b);
    cout << (negative ? "-" : "") << Polynom::to_string(p);
}
