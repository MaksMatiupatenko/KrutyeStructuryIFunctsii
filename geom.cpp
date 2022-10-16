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
    int sign(type n) {
        if (n == 0) return 0;
        if (n > 0) return 1;
        return -1;
    }

    template <class type>
    bool pointInSegment(const Vector2 <type>& point, const Vector2 <type>& sg1, const Vector2 <type>& sg2) {
        return dot(sg1 - point, sg2 - point) <= 0 && cross(sg1 - point, sg2 - point) == 0;
    }

    template <class type>
    bool pointInAngle(const Vector2 <type>& point, const Vector2 <type>& sg1, const Vector2 <type>& sg2) {
        return (sign(cross(sg1, point)) * sign(cross(sg2, point)) < 0) && point.x > 0;
    }

    template <class type>
    class Polygon {
    private:
        vector <Vector2 <type>> data;
        bool isConvex = false;

    public:
        Vector2 <type>& operator[](int ind) {
            return data[(ind % (int)data.size() + (int)data.size()) % (int)data.size()];
        }

        int size() {
            return data.size();
        }

        void push(const Vector2 <type>& vertex) {
            data.push_back(vertex);
            isConvex = false;
        }

        Vector2 <type> segment(int ind) {
            return (*this)[ind + 1] - (*this)[ind];
        }

        void createConvexHull() {
            sort(all(data), [&](const Vector2 <type>& v1, const Vector2 <type>& v2) {
                if (v1.x == v2.x) return v1.y < v2.y;
                return v1.x < v2.x;
                });
            data.resize(unique(all(data)) - data.begin());
            sort(data.begin() + 1, data.end(), [&](const Vector2 <type>& v1, const Vector2 <type>& v2) {
                type cr = cross(v1 - data[0], v2 - data[0]);
                if (cr == 0) return length2(v1 - data[0]) < length2(v2 - data[0]);
                return cr > 0;
                });

            vector <Vector2 <type>> st;
            for (int i = 0; i < size(); ++i) {
                while (st.size() > 1 && cross(st.back() - st[st.size() - 2], data[i] - st.back()) <= 0) {
                    st.pop_back();
                }
                st.push_back(data[i]);
            }

            data = st;
            isConvex = true;
        }

        type area2() {
            type ans = 0;
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
        int contains(Vector2 <type> point) {
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

        pair <int, int> parallelTangents(const Vector2 <type>& vec) {
            auto& p = *this;

            Vector2 <type> vec1 = { vec.y, -vec.x };

            int lg = 0;
            while ((1 << lg) < size()) ++lg;

            int i1 = 0;
            for (int k = lg; k >= 0; --k) {
                int ni = i1;
                Vector2 <type> v1 = p[i1 - (1 << k)];
                Vector2 <type> v2 = p[i1];
                Vector2 <type> v3 = p[i1 + (1 << k)];

                if (dot(v1, vec1) < dot(v2, vec1)) {
                    v1 = v2;
                    ni = i1 - (1 << k);
                }
                if (dot(v1, vec1) < dot(v3, vec1)) {
                    ni = i1 + (1 << k);
                }
                i1 = ni;
            }

            int i2 = 0;
            for (int k = lg; k >= 0; --k) {
                int ni = i2;
                Vector2 <type> v1 = p[i2 - (1 << k)];
                Vector2 <type> v2 = p[i2];
                Vector2 <type> v3 = p[i2 + (1 << k)];

                if (dot(v1, vec1) > dot(v2, vec1)) {
                    v1 = v2;
                    ni = i2 - (1 << k);
                }
                if (dot(v1, vec1) > dot(v3, vec1)) {
                    ni = i2 + (1 << k);
                }
                i2 = ni;
            }

            return { i1, i2 };
        }
    };
}