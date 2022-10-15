void calc(int ql, int qr, int optl, int optr, int layer, vector <vector <int64>>& dp, const vector <vector <int64>>& sg) {
    if (ql == qr) return;

    int m = (ql + qr) / 2;
    int opt = optl;
    dp[m][layer] = 1e18;
    for (int i = optl; i <= min(m - 1, optr); ++i) {
        if (dp[i][layer - 1] + sg[i + 1][m + 1] < dp[m][layer]) {
            opt = i;
            dp[m][layer] = dp[i][layer - 1] + sg[i + 1][m + 1];
        }
    }

    if (ql + 1 < qr) {
        calc(ql, m, optl, opt, layer, dp, sg);
        calc(m, qr, opt, optr, layer, dp, sg);
    }

}
