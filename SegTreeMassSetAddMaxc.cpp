class SegmentTree {
private:
    enum class FlagType {
        NONE,
        ADD,
        SET
    };
    struct Flag {
        FlagType flagType = FlagType::NONE;
        int data = 0;
    };
    static const int NEUTRAL = INT32_MIN;
    struct Info {
        int value = NEUTRAL;
        Flag flag = Flag();
        void apply(const Flag& newFlag) {
            if (newFlag.flagType == FlagType::NONE) {
                return;
            }
            if (newFlag.flagType == FlagType::ADD) {
                value += newFlag.data;
            } else if (newFlag.flagType == FlagType::SET) {
                value = newFlag.data;
            }
            if (flag.flagType == newFlag.flagType) {
                if (flag.flagType == FlagType::ADD) {
                    flag.data += newFlag.data;
                } else {
                    flag.data = newFlag.data;
                }
            } else {
                flag = newFlag;
            }
        }
    };
    vector <Info> treeData;
    int treeSize{};
    void recalculateNode(int i) {
        if (i < treeSize) {
            treeData[i].value = max(
                    treeData[2 * i].value,
                    treeData[2 * i + 1].value);
        }
    }
    void applyFlag(int i, const Flag& flag) {
        treeData[i].apply(flag);
    }
    void pushFlag(int i) {
        if (i < treeSize) {
            applyFlag(2 * i, treeData[i].flag);
            applyFlag(2 * i + 1, treeData[i].flag);
            treeData[i].flag = Flag{};
        }
    }
    int getMaximum(int queryLeft, int queryRight, int segmentLeft, int segmentRight, int i) {
        if (segmentLeft >= queryRight || queryLeft >= segmentRight || segmentLeft >= segmentRight) {
            return NEUTRAL;
        }
        if (queryLeft <= segmentLeft && segmentRight <= queryRight) {
            pushFlag(i);
            return treeData[i].value;
        }
        pushFlag(i);
        int segmentMiddle = (segmentLeft + segmentRight) / 2;
        return max(getMaximum(queryLeft, queryRight, segmentLeft, segmentMiddle, 2 * i),
                   getMaximum(queryLeft, queryRight, segmentMiddle, segmentRight, 2 * i + 1));
    }
    void applyFlag(int queryLeft, int queryRight, int segmentLeft, int segmentRight, int i, const Flag& flag) {
        if (segmentLeft >= queryRight || queryLeft >= segmentRight || segmentLeft >= segmentRight) {
            return;
        }
        if (queryLeft <= segmentLeft && segmentRight <= queryRight) {
            pushFlag(i);
            return applyFlag(i, flag);
        }
        pushFlag(i);
        int segmentMiddle = (segmentLeft + segmentRight) / 2;
        applyFlag(queryLeft, queryRight, segmentLeft, segmentMiddle, 2 * i, flag),
        applyFlag(queryLeft, queryRight, segmentMiddle, segmentRight, 2 * i + 1, flag);
        recalculateNode(i);
    }
public:
    explicit SegmentTree(const vector <int>& v) {
        treeSize = 1;
        while (treeSize < (int) v.size()) {
            treeSize *= 2;
        }
        treeData.resize(2 * treeSize, Info());
        for (int i = 0; i < (int) v.size(); ++i) {
            treeData[i + treeSize].value = v[i];
        }
        for (int i = treeSize - 1; i > 0; --i) {
            recalculateNode(i);
        }
    }
    int getMaximum(int l, int r) {
        return getMaximum(l, r, 0, treeSize, 1);
    }
    void addOnSegment(int l, int r, int x) {
        return applyFlag(l, r, 0, treeSize, 1, {
                FlagType::ADD,
                x
        });
    }
    void setOnSegment(int l, int r, int x) {
        return applyFlag(l, r, 0, treeSize, 1, {
                FlagType::SET,
                x
        });
    }
};
