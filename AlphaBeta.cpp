mt19937 mt(1337);
function<int(int, int, int, int, int)> dfs = [&](int l, int r, int playerId, int alpha, int beta) {
    if (l == r - 1) {
        return ((l * l) % m * a + b * l + c) % m;
    }
    int mid = (l + r) / 2;
    vector<pair<int, int> > moves = {
            {l,   mid},
            {mid, r}
    };
    shuffle(all(moves), mt);
    if (playerId == 0) {
        int res1 = dfs(moves[0].first, moves[0].second, 1 - playerId, alpha, beta);
        if (res1 >= beta) {
            return res1;
        }
        alpha = max(alpha, res1);
        return max(res1, dfs(moves[1].first, moves[1].second, 1 - playerId, alpha, beta));
    } else {
        int res1 = dfs(moves[0].first, moves[0].second, 1 - playerId, alpha, beta);
        if (res1 <= alpha) {
            return res1;
        }
        beta = min(beta, res1);
        return min(res1, dfs(moves[1].first, moves[1].second, 1 - playerId, alpha, beta));
    }
};
cout << dfs(0, (1 << n), 0, INT64_MIN, INT64_MAX);
