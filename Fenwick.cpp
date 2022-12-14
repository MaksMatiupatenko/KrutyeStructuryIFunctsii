//TUT POLUINTERVALY!!!
class Fenwick {
private:
    std::vector <int> data;

    int get(int l) {
        int ans = 0;
        for (; l >= 0; l = (l & (l + 1)) - 1) {
            ans += data[l];
        }
        return ans;
    }

public:
    Fenwick(int size) {
        data.assign(size, 0);
    }

    void add(int pos, int x) {
        for (; pos < data.size(); pos |= pos + 1) {
            data[pos] += x;
        }
    }

    int get(int l, int r) {
        return get(r - 1) - get(l - 1);
    }
};
