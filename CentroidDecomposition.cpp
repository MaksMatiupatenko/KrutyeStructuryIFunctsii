class CentroidDecomposition {
private:
    vector <vector <int> > g;
    vector<int> level, parent, sizes;
    
    function<void(int, int)> calcSizes = [&](int curr, int par) {
        sizes[curr] = 1;
        for (auto t: g[curr]) {
            if (t != par && !level[t]) {
                calcSizes(t, curr);
                sizes[curr] += sizes[t];
            }
        }
    };
    
    function<void(int, int, int, int)> centroid = [&](int curr, int par, int prevCentroid, int sz0) {
        int mx = 0;
        for (auto to: g[curr]) {
            if (to != par && !level[to]) {
                mx = max(mx, sizes[to]);
            }
        }
        if (mx * 2 <= sz0) {
            parent[curr] = prevCentroid;
            if (prevCentroid != -1) {
                level[curr] = level[prevCentroid] + 1;
            } else {
                level[curr] = 1;
            }
            for (auto to: g[curr]) {
                if (!level[to]) {
                    calcSizes(to, -1);
                    centroid(to, -1, curr, sizes[to]);
                }
            }
            return;
        }
        bool f = false;
        for (auto to: g[curr]) {
            if (to != par && !level[to]) {
                if (sizes[to] == mx && !f) {
                    centroid(to, curr, prevCentroid, sz0);
                    f = true;
                }
            }
        }
    };

public:
    explicit CentroidDecomposition(const vector <vector <int> >& g) : g(g) {
        int n = sz(g);
        sizes.assign(n, 0);
        level.assign(n, 0);
        parent.assign(n, -1);
        calcSizes(0, -1);
        centroid(0, -1, -1, sizes[0]);
    }

    vector <int>& getLevel() {
        return level;
    }

    vector <int>& getParent() {
        return parent;
    }
};
