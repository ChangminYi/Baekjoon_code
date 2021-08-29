#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

const int NOT_VISIT = -1;
const vector<pint> pos_dir = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

int n;
vector<vector<int>> board;
vector<vector<int>> dp;

bool in_range(const pint& p) {
	if (0 <= p.first && p.first < n && 0 <= p.second && p.second < n) {
		return true;
	}
	return false;
}

int dfs(pint cur, int depth) {
	bool can_go = false;

	int max_val = 0;
	for (const pint& p : pos_dir) {
		pint nxt = make_pair(cur.first + p.first, cur.second + p.second);

		if (in_range(nxt) && board[cur.first][cur.second] < board[nxt.first][nxt.second]) {
			can_go = true;
			if (dp[nxt.first][nxt.second] == NOT_VISIT) {
				max_val = max(max_val, dfs(nxt, depth + 1));
			}
			else {
				max_val = max(max_val, dp[nxt.first][nxt.second]);
			}
		}
	}

	return dp[cur.first][cur.second] = (can_go ? max_val + 1 : 1);
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> n;
	board = vector<vector<int>>(n, vector<int>(n));
	dp = vector<vector<int>>(n, vector<int>(n, NOT_VISIT));
	for (vector<int>& row : board) {
		for (int& i : row) {
			cin >> i;
		}
	}

	int res = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (dp[i][j] == NOT_VISIT) {
				res = max(res, dfs(make_pair(i, j), 1));
			}
		}
	}

	cout << res;

	return 0;
}