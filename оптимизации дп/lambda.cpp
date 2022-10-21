int64 l = -8e13, r = 1;
    while (l + 1 != r) {
        int64 m = (l + r) / 2;

        vector <pair <int64, pair <int, int>>> dp(n, { 0, {0, 0} });
        vector <int> hasSg(n, 0);
        hasSg[1] = 1;
        dp[1] = { v[1] - v[0] + m, {1, 1} };
        if (0 == dp[1].first) {
            dp[1] = { 0, {0, 1} };
            hasSg[1] = 2;
        }
        else if (0 < dp[1].first) {
            dp[1] = { 0, {0, 0} };
            hasSg[1] = 0;
        }

        for (int i = 2; i < n; ++i) {
            if (dp[i - 2].first + v[i] - v[i - 1] + m == dp[i - 1].first) {
                dp[i] = { dp[i - 1].first, {
                        min(dp[i - 1].second.first, dp[i - 2].second.first + 1),
                        max(dp[i - 1].second.second, dp[i - 2].second.second + 1)} };
                hasSg[i] = 2;
            }
            else if (dp[i - 2].first + v[i] - v[i - 1] + m < dp[i - 1].first) {
                dp[i] = { dp[i - 2].first + v[i] - v[i - 1] + m, {dp[i - 2].second.first + 1, dp[i - 2].second.second + 1} };
                hasSg[i] = 1;
            }
            else {
                dp[i] = { dp[i - 1].first, dp[i - 1].second };
                hasSg[i] = 0;
            }
        }

        if (dp[n - 1].second.first <= k && k <= dp[n - 1].second.second) {
            cout << dp[n - 1].first - k * m << '\n';
            int i = n - 1;
            while (i > 0) {
                if (hasSg[i] == 1) {
                    cout << i << ' ' << i + 1 << '\n';
                    --k;
                    i -= 2;
                }
                else if (hasSg[i] == 0) {
                    --i;
                }
                else {
                    if (dp[i - 1].second.first <= k && k <= dp[i - 1].second.second) {
                        --i;
                    }
                    else {
                        cout << i << ' ' << i + 1 << '\n';
                        --k;
                        i -= 2;
                    }
                }
            }
            return 0;
        }
