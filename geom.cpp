namespace geom {
    const double PI = acos(-1);

    template <class type>
    class Vector2 {
    public:
        type x, y;
        Vector2(type x = 0, type y = 0) :x(x), y(y) {}

        friend istream& operator>>(istream& is, Vector2 <type>& vec) {
            return is >> vec.x >> vec.y;
        }
        friend ostream& operator<<(ostream& os, const Vector2 <type>& vec) {
            return os << vec.x << ' ' << vec.y;
        }

        Vector2 <type> operator*(const type& n) const {
            return Vector2 <type>(x * n, y * n);
        }
        Vector2 <type> operator/(const type& n) const {
            return Vector2 <type>(x / n, y / n);
        }

        Vector2 <type> operator-() const {
            return Vector2 <type>(-x, -y);
        }

        Vector2 <type> operator+(const Vector2 <type>& v) const {
            return Vector2 <type>(x + v.x, y + v.y);
        }
        Vector2 <type> operator-(const Vector2 <type>& v) const {
            return Vector2 <type>(x - v.x, y - v.y);
        }
        Vector2 <type> operator*(const Vector2 <type>& v) const {
            return Vector2 <type>(x * v.x, y * v.y);
        }
        Vector2 <type> operator/(const Vector2 <type>& v) const {
            return Vector2 <type>(x / v.x, y / v.y);
        }

        bool operator==(const Vector2 <type>& v) const {
            return x == v.x && y == v.y;
        }
        bool operator!=(const Vector2 <type>& v) const {
            return x != v.x || y != v.y;
        }

        friend type length2(const Vector2 <type>& vec) {
            return vec.x * vec.x + vec.y * vec.y;
        }
        friend double length(const Vector2 <type>& vec) {
            return sqrt(length2(vec));
        }

        friend type dot(const Vector2 <type>& v1, const Vector2 <type>& v2) {
            return v1.x * v2.x + v1.y * v2.y;
        }
        friend type cross(const Vector2 <type>& v1, const Vector2 <type>& v2) {
            return v1.x * v2.y - v1.y * v2.x;
        }

        friend double atan(const Vector2 <type>& vec) {
            return atan2(vec.y, vec.x);
        }
        friend double atan(const Vector2 <type>& v1, const Vector2 <type>& v2) {
            return atan2(cross(v1, v2), dot(v1, v2));
        }
    };
    using vec2 = Vector2 <double>;
    using ivec2 = Vector2 <int64>;

    template <class type>
    struct Line {
        type A = 1, B = 1, C = 0;

        Line(type A, type B, type C) : A(A), B(B), C(C) {}

        Line(const Vector2 <type>& p1, const Vector2 <type>& p2) {
            auto [x1, y1] = p1;
            auto [x2, y2] = p2;
            A = (y1 - y2);
            B = (x2 - x1);
            C = (x1 * y2 - x2 * y1);
        }

        type operator()(const Vector2 <type>& a) const {
            return A * a.x + B * a.y + C;
        }

        Vector2 <type> getNorm() const {
            return { A, B };
        }

        friend Vector2 <double> intersection(const Line& a, const Line& b) {

        }
    };

    template <class type>
    int sign(type n) {
        if (n == 0) return 0;
        if (n > 0) return 1;
        return -1;
    }

    template <class vec_t>
    bool pointInSegment(const vec_t& point, const vec_t& sg1, const vec_t& sg2) {
        return dot(sg1 - point, sg2 - point) <= 0 && cross(sg1 - point, sg2 - point) == 0;
    }

    template <class vec_t>
    bool pointInAngle(const vec_t& point, const vec_t& sg1, const vec_t& sg2) {
        return (sign(cross(sg1, point)) * sign(cross(sg2, point)) < 0) && point.x > 0;
    }

    template <class vec_t>
    class Polygon {
    private:
        vector <vec_t> data;
        bool isConvex = false;
        int mnx = 0, mxx = 0;

    public:
        vec_t& operator[](int ind) {
            return data[(ind % (int)data.size() + (int)data.size()) % (int)data.size()];
        }

        int size() {
            return data.size();
        }

        void push(const vec_t& vertex) {
            data.push_back(vertex);
            isConvex = false;
            if (data.back().x < data[mnx].x) {
                mnx = data.size() - 1;
            }
            if (data.back().x > data[mxx].x) {
                mxx = data.size() - 1;
            }
        }

        vec_t segment(int ind) {
            return (*this)[ind + 1] - (*this)[ind];
        }

        void createConvexHull() {
            sort(all(data), [&](const vec_t& v1, const vec_t& v2) {
                if (v1.x == v2.x) return v1.y < v2.y;
                return v1.x < v2.x;
                });
            data.resize(unique(all(data)) - data.begin());
            sort(data.begin() + 1, data.end(), [&](const vec_t& v1, const vec_t& v2) {
                typename vec_t::type cr = cross(v1 - data[0], v2 - data[0]);
                if (cr == 0) return length2(v1 - data[0]) < length2(v2 - data[0]);
                return cr > 0;
                });

            vector <vec_t> st;
            for (int i = 0; i < size(); ++i) {
                while (st.size() > 1 && cross(st.back() - st[st.size() - 2], data[i] - st.back()) <= 0) {
                    st.pop_back();
                }
                st.push_back(data[i]);
            }

            data = st;
            isConvex = true;

            mnx = 0, mxx = 0;
            for (int i = 0; i < data.size(); ++i) {
                if (data[i].x < data[mnx].x) {
                    mnx = i;
                }
                if (data[i].x > data[mxx].x) {
                    mxx = i;
                }
            }
        }

        vec_t::type area2() {
            typename vec_t::type ans = 0;
            for (int i = 0; i < size(); ++i) {
                ans += cross(data[i], data[(i + 1) % data.size()]);
            }
            return ans;
        }

        double perimetr() {
            double ans = 0;
            for (int i = 0; i < size(); ++i) {
                ans += length(segment(i));
            }
            return ans;
        }

        // -1 if outside
        // 0 if border
        // 1 if inside
        int contains(vec_t point) {
            auto& p = *this;

            if (!isConvex) {
                double angle = 0;
                for (int i = 0; i < data.size(); ++i) {
                    if (pointInSegment(point, p[i], p[i + 1])) {
                        return 0;
                    }
                    angle += atan(p[i] - point, p[i + 1] - point);
                }

                if (abs(angle) > PI) return 1;
                else return -1;
            }

            if (pointInSegment(point, p[0], p[1]) || pointInSegment(point, p[0], p[-1])) {
                return 0;
            }
            if (!pointInAngle(point - p[0], p[1] - p[0], p[-1] - p[0])) {
                return -1;
            }


            int l = 1, r = p.size() - 1;
            while (l + 1 != r) {
                int m = (l + r) / 2;

                if (cross(point - p[0], p[m] - p[0]) <= 0) l = m;
                else r = m;
            }

            if (pointInSegment(point - p[0], p[l] - p[0], p[l + 1] - p[0])) {
                return 0;
            }
            else if (cross(p[l + 1] - p[l], point - p[l]) > 0) {
                return 1;
            }
            else {
                return -1;
            }
        }

        pair <int, int> parallelTangents(const vec_t& vec) {
            auto& p = *this;

            vec_t norm = { vec.y, -vec.x };
            if (norm.y < 0) norm = -norm;

            int l1 = mnx - 1, r1 = mxx;
            while (l1 + 1 != r1) {
                int m = (l1 + r1) / 2;
                if (dot(p.segment(m), norm) <= 0) l1 = m;
                else r1 = m;
            }

            int l2 = mxx - 1, r2 = mnx + p.size();
            while (l2 + 1 != r2) {
                int m = (l2 + r2) / 2;
                if (dot(p.segment(m), norm) >= 0) l2 = m;
                else r2 = m;
            }

            return { r1, r2 };
        }

        pair <int, int> tangents(const vec_t& point) {
            auto& p = *this;

            int lg = 0;
            while ((1 << lg) < p.size()) ++lg;

            int l1 = 0;
            for (int k = lg; k >= 0; --k) {
                vec_t v1 = p[l1 - (1 << k)] - point;
                vec_t v2 = p[l1] - point;
                vec_t v3 = p[l1 + (1 << k)] - point;

                if (cross(v1, v2) < 0 && cross(v1, v3) < 0) {
                    l1 = l1 - (1 << k);
                }
                else if (cross(v3, v2) < 0 && cross(v3, v1) < 0) {
                    l1 = l1 + (1 << k);
                }
                l1 %= p.size();
            }

            int l2 = 0;
            for (int k = lg; k >= 0; --k) {
                vec_t v1 = p[l2 - (1 << k)] - point;
                vec_t v2 = p[l2] - point;
                vec_t v3 = p[l2 + (1 << k)] - point;

                if (cross(v1, v2) > 0 && cross(v1, v3) > 0) {
                    l2 = l2 - (1 << k);
                }
                else if (cross(v3, v2) > 0 && cross(v3, v1) > 0) {
                    l2 = l2 + (1 << k);
                }
                l2 %= p.size();
            }

            return { l1, l2 };
        }
    };

    // not strict intersection
    template <class vec_t>
    bool isIntersect(const vec_t& a1, const vec_t& b1, const vec_t& a2, const vec_t& b2) {
        if (
            cross(b1 - a1, a2 - b1) == 0 && cross(b1 - a1, b2 - b1) == 0 &&
            cross(b2 - a2, a1 - b2) == 0 && cross(b2 - a2, b1 - b2) == 0) {

            return 
                dot(a1 - a2, b1 - a2) <= 0 || dot(a1 - b2, b1 - b2) <= 0 ||
                dot(a2 - a1, b2 - a1) <= 0 || dot(a2 - b1, b2 - b1) <= 0;
        }

        return
            sign(cross(a1 - a2, b2 - a2)) * sign(cross(b1 - a2, b2 - a2)) <= 0 &&
            sign(cross(a2 - a1, b1 - a1)) * sign(cross(b2 - a1, b1 - a1)) <= 0;
    }
}
