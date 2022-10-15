template <class type, class cmp = std::less <type>>
class SparseTable {
private:
    std::vector <int> bitFloor;
    std::vector <vector <int>> data;
    std::vector <type> initData;

    int m_min(int a, int b) const {
        if (cmp()(initData[b], initData[a])) return b;
        return a;
    }

public:
    SparseTable(const std::vector <type>& init) {
        bitFloor.assign(init.size() + 1, -1);
        for (int i = 1; i < bitFloor.size(); ++i) {
            bitFloor[i] = bitFloor[i / 2] + 1;
        }

        initData = init;

        data.assign(bitFloor.back() + 1, vector <int> (init.size()));
        iota(all(data[0]), 0);
        for (int l = 1; l < data.size(); ++l) {
            for (int i = 0; i + (1 << l) <= init.size(); ++i) {
                data[l][i] = m_min(data[l - 1][i], data[l - 1][i + (1 << (l - 1))]);
            }
        }
    }

    int getInd(int l, int r) const {
        return m_min(data[bitFloor[r - l]][l], data[bitFloor[r - l]][r - (1 << bitFloor[r - l])]);
    }

    type getVal(int l, int r) const {
        return initData[getInd(l, r)];
    }
};
