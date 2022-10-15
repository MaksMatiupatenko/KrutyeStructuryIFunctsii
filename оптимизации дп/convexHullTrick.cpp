vector <pair <int64, int64>> lines = { {b[0], dp[0]} };
    vector <double> points = { -1e9 };
    for (int i = 1; i < n; ++i) {
        int l = lower_bound(all(points), a[i]) - points.begin() - 1;
        dp[i] = lines[l].first * a[i] + lines[l].second;
        
        while (intersect(lines.back(), { b[i], dp[i] }) < points.back()) {
            points.pop_back();
            lines.pop_back();
        }
        points.push_back(intersect(lines.back(), { b[i], dp[i] }));
        lines.push_back({ b[i], dp[i] });
    }
