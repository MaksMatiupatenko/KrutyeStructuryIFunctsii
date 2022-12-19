namespace Allocator {
    static const int mem = 1e7;
    static char data[mem];
    static int cps = 0;

    template <class type>
    class ptr {
    public:
        int pos = -1;

        ptr() {}
        ptr(nullptr_t) {}

        type& operator*() {
            return *(type*)(data + pos);
        }

        type* operator->() {
            return (type*)(data + pos);
        }

        bool operator!() const {
            return pos == -1;
        }

        bool operator==(nullptr_t) const {
            return pos == -1;
        }

        operator void*() const {
            return data + pos;
        }
    };

    template <class type>
    ptr <type> allocate(const type& val) {
        ptr <type> p;
        p.pos = cps;
        *(type*)(data + cps) = val;
        cps += sizeof(type);
        return p;
    }
};
