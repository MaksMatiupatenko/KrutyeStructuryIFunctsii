template <class Iter>
vector <int> zFunc(Iter begin, Iter end) {
    vector <int> ans(end - begin, 0);
    ans[0] = end - begin;
    int zEnd = 0, zBegin = 0;
    for (int i = 1; i < end - begin; ++i) {
        if (i < zEnd) {
            ans[i] = max(min(zEnd - i, ans[i - zBegin]), ans[i]);
        }
        while (begin + i + ans[i] < end && begin[ans[i]] == begin[i + ans[i]]) {
            ++ans[i];
        }
        if (zEnd < i + ans[i]) {
            zEnd = i + ans[i];
            zBegin = i;
        }
    }
    return ans;
}
