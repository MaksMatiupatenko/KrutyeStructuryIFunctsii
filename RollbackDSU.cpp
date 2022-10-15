class DSU {
private:
    std::vector <int> pr, height;
    std::vector <std::pair <int, int>> st;

    int get(int u) {
        if (u == pr[u]) return u;
        return get(pr[u]);
    }

public:
    DSU(int n = 0) {
        reset(n);
    }

    void reset(int n) {
        pr.resize(n);
        height.assign(n, 1);
        for (int i = 0; i < n; i++)
            pr[i] = i;
    }

    void unite(int u, int v) {
        st.push_back({ -1, 0 });

        u = get(u);
        v = get(v);
        if (u == v) return;
        if (height[u] > height[v]) std::swap(u, v);
        pr[u] = v;
        st.back().first = u;
        if (height[u] == height[v]) {
            height[v]++;
            st.back().second = 1;
        }
    }

    bool check(int u, int v) {
        return get(u) == get(v);
    }

    void rollback() {
        if (st.back().first != -1) {
            if (st.back().second) {
                height[pr[st.back().first]]--;
            }
            pr[st.back().first] = st.back().first;
        }
        st.pop_back();
    }
};
