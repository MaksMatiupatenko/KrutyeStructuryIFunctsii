vector<bool> bigParentEdge(n);
    vector<int> sizes(n);
    vector<int> pos(n);
    vector<int> closestSmall(n);
    vector<int> parent(n);
    vector<int> order, order1;
    function<void(int, int)> dfs = [&](int curr, int par) {
        parent[curr] = par;
        sizes[curr] = 1;
        for (int i = 0; i + 1 < sz(g[curr]); ++i) {
            int to = g[curr][i];
            if (to == par) {
                swap(g[curr][sz(g[curr]) - 1], g[curr][i]);
                break;
            }
        }
        for (auto to: g[curr]) {
            if (to != par) {
                dfs(to, curr);
                sizes[curr] += sizes[to];
            }
        }
        for (int i = 1; i < sz(g[curr]); ++i) {
            int to = g[curr][i];
            if (sizes[to] > sizes[g[curr][0]] && to != par) {
                swap(g[curr][i], g[curr][0]);
            }
        }
    };
    dfs(0, -1);
    function<void(int, int)> getOrder = [&](int curr, int par) {
        pos[curr] = sz(order);
        order.push_back(v[curr]);
        order1.push_back(curr);
        for (auto to: g[curr]) {
            if (to != par) {
                getOrder(to, curr);
            }
        }
    };
    getOrder(0, -1);
    for (auto i: order1) {
        if (sz(g[i]) > 1) {
            bigParentEdge[g[i][0]] = true;
        }
        for (auto j: g[i]) {
            if (j != parent[i]) {
                if (bigParentEdge[j]) {
                    closestSmall[j] = closestSmall[i];
                } else {
                    closestSmall[j] = j;
                }
            }
        }
    }
    LCA lca(g);
    SegmentTree segmentTree(order);
    auto getVerticalPathAns = [&](int a, int b) {
        int ans = INT32_MIN;
        while (a != b) {
            while (!bigParentEdge[a] && a != b) {
                ans = max(ans, v[a]);
                a = parent[a];
            }
            if (a != b) {
                int l = max(pos[b], pos[closestSmall[a]]);
                int r = pos[a];
                ans = max(ans, segmentTree.get(l, r + 1));
                if (pos[closestSmall[a]] < pos[b]) {
                    a = b;
                } else {
                    a = closestSmall[a];
                }
            }
        }
        return max(ans, v[b]);
    };
    int q;
    cin >> q;
    while (q--) {
        char t;
        cin >> t;
        if (t == '?') {
            int a, b;
            cin >> a >> b;
            --a, --b;
            int r = lca.get(a, b);
            cout << max(getVerticalPathAns(a, r), getVerticalPathAns(b, r)) << '\n';
        } else {
            int i, x;
            cin >> i >> x;
            --i;
            segmentTree.set(pos[i], x);
            v[i] = x;
       
