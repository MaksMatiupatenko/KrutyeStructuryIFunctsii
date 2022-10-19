int kuhn(int v, const vector <vector <int>>& g, vector <int>& used, int timer, vector <int>& res) {
    if (used[v] == timer) return 0;

    used[v] = timer;

    for (auto u : g[v]) {
        if (res[u] == -1) {
            res[u] = v;
            return 1;
        }
    }
    for (auto u : g[v]) {
        if (kuhn(res[u], g, used, timer, res)) {
            res[u] = v;
            return 1;
        }
    }

    return 0;
}
