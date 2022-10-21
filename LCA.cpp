class LCA {
private:
    vector<vector<int> > g;
    vector<int> pos;
    vector<int> order;
    vector<int> depth;
    SparseTable sparseTable;
    int n;

    void dfs(int curr = 0, int par = -1) {
        pos[curr] = sz(order);
        order.push_back(curr);
        for (auto to: g[curr]) {
            if (to != par) {
                depth[to] = depth[curr] + 1;
                dfs(to, curr);
                order.push_back(curr);
            }
        }
    }

public:
    explicit LCA(const vector<vector<int> > &ng) : g(ng) {
        n = sz(g);
        pos.resize(n), depth.resize(n);
        dfs();
        int m = sz(order);
        vector<pair<int, int> > tt(m);
        for (int i = 0; i < m; ++i) {
            tt[i] = {depth[order[i]], order[i]};
        }
        sparseTable = SparseTable(tt);
    }

    int get(int a, int b) {
        a = pos[a], b = pos[b];
        if (a > b) {
            swap(a, b);
        }
        return sparseTable.get(a, b);
    }
};
