template <class Iter>
vector <int> prefFunc(Iter begin, Iter end) {
    vector <int> ans(end - begin, 0);
    for (int i = 1; i < end - begin; ++i) {
        int j = ans[i - 1];
        while (j > 0 && begin[i] != begin[j]) {
            j = ans[j - 1];
        }
        ans[i] = j;
        if (begin[i] == begin[j]) {
            ++ans[i];
        }
    }
    return ans;
}
