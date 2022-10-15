class DSU {
private:
    std::vector <int> pr, height;

    int get(int u) {
        if (u == pr[u]) return u;
        return pr[u] = get(pr[u]);
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
        u = get(u);
        v = get(v);
        if (u == v) return;
        if (height[u] > height[v]) std::swap(u, v);
        pr[u] = v;
        if (height[u] == height[v]) height[v]++;
    }

    bool check(int u, int v) {
        return get(u) == get(v);
    }
};
