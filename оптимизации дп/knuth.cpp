for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len <= n; ++i) {
            int opt = i + 1;
            int64 optans = 1e18;

            int l = i + 1;
            if (i > 0) l = max(l, dp[i][i + len - 1].first);
            int r = i + len - 1;
            if (i + len + 1 <= n) r = min(dp[i + 1][i + len].first, r);

            for (int j = l; j <= r; ++j) {
                if (dp[i][j].second + dp[j][i + len].second < optans) {
                    opt = j;
                    optans = dp[i][j].second + dp[j][i + len].second;
                }
            }

            dp[i][i + len] = {opt, optans + pr[i + len] - pr[i]};
        }
    }
