namespace karatsuba {
    const int64 BASE = 1e9;

    vector <int64> toPolynom(string s) {
        while (s.size() % 9 != 0) {
            s.insert(s.begin(), '0');
        }
        vector <int64> ans;
        for (int i = 0; i < s.size(); ++i) {
            if (i % 9 == 0) {
                ans.push_back(0);
            }
            ans.back() *= 10;
            ans.back() += (s[i] - '0');
        }
        reverse(all(ans));
        return ans;
    }
    string toString(const vector <int64>& v) {
        reverse(all(v));
        string ans = to_string(v[0]);
        for (int i = 1; i < v.size(); ++i) {
            string s = to_string(v[i]);
            while (s.size() < 9) {
                s.insert(s.begin(), '0');
            }
            ans += s;
        }

        return ans;
    }

    int64 mdiv(int64 a, int64 b) {
        if (a < 0) {
            return (a - b + 1) / b;
        }
        return a / b;
    }
    int64 mmod(int64 a, int64 b) {
        return ((a % b) + b) % b;
    }

    void equalize(vector <int64>& a, vector <int64>& b) {
        while (a.size() < b.size()) {
            a.push_back(0);
        }
        while (b.size() < a.size()) {
            b.push_back(0);
        }
    }
    void normalize(vector <int64>& v) {
        int64 carry = 0;
        for (int i = 0; i < v.size(); ++i) {
            v[i] += carry;
            carry = mdiv(v[i], BASE);
            v[i] = mmod(v[i], BASE);
        }
        while (carry > 0) {
            v.push_back(mmod(carry, BASE));
            carry = mdiv(carry, BASE);
        }

        while (v.size() > 1 && v.back() == 0) {
            v.pop_back();
        }
    }

    vector <int64> sum(vector <int64>& a, vector <int64>& b) {
        equalize(a, b);
        vector <int64> ans = a;
        for (int i = 0; i < a.size(); ++i) {
            ans[i] += b[i];
        }
        normalize(ans);
        return ans;
    }
    vector <int64> diff(vector <int64>& a, vector <int64>& b) {
        equalize(a, b);
        vector <int64> ans = a;
        for (int i = 0; i < a.size(); ++i) {
            ans[i] -= b[i];
        }
        normalize(ans);
        return ans;
    }
    vector <int64> mulPowBase(vector <int64>& v, int pw) {
        vector <int64> ans(pw, 0);
        for (auto& x : v) ans.push_back(x);
        normalize(ans);
        return ans;
    }
    vector <int64> mul1(vector <int64>& v, int64 n) {
        vector <int64> ans = v;
        for (int i = 0; i < v.size(); ++i) {
            ans[i] *= n;
        }
        normalize(ans);
        return ans;
    }

    vector <int64> mul2(vector <int64>& a, vector <int64>& b) {
        equalize(a, b);
        vector <int64> ans = { 0 };
        for (int i = 0; i < a.size(); ++i) {
            vector <int64> tmp = mul1(a, b[i]);
            tmp = mulPowBase(tmp, i);
            ans = sum(ans, tmp);
        }
        normalize(ans);
        return ans;
    }

    vector <int64> mul(vector <int64> a, vector <int64> b) {
        equalize(a, b);
        if (a.size() <= 32) {
            return mul2(a, b);
        }

        int sz = a.size() / 2;
        vector <int64> a1(a.begin(), a.begin() + sz);
        vector <int64> a2(a.begin() + sz, a.end());
        vector <int64> b1(b.begin(), b.begin() + sz);
        vector <int64> b2(b.begin() + sz, b.end());

        vector <int64> a1b1 = mul(a1, b1);
        vector <int64> a2b2 = mul(a2, b2);

        vector <int64> sma = sum(a1, a2);
        vector <int64> smb = sum(b1, b2);
        vector <int64> tmp = mul(sma, smb);
        tmp = diff(tmp, a1b1);
        tmp = diff(tmp, a2b2);

        tmp = mulPowBase(tmp, sz);
        a2b2 = mulPowBase(a2b2, sz * 2);

        vector <int64> ans = a2b2;
        ans = sum(ans, tmp);
        ans = sum(ans, a1b1);

        normalize(ans);
        return ans;
    }
}
