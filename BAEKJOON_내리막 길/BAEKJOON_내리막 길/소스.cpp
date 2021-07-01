#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

const int NOT_VISIT = -1;
const vector<pint> mov_dir = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}
};
int m, n;
vector<vector<int>> board, dp_cnt;

bool in_range(pint& p) {
	if (0 <= p.first && p.first < m) {
		if (0 <= p.second && p.second < n) {
			return true;
		}
	}
	return false;
}

bool is_end(pint& p) {
	if (p.first == m - 1 && p.second == n - 1) {
		return true;
	}
	return false;
}

int dfs(pint cur) {
	if (is_end(cur)) {
		return 1;
	}
	else if (dp_cnt[cur.first][cur.second] == NOT_VISIT) {
		dp_cnt[cur.first][cur.second] = 0;

		for (const pint& mov : mov_dir) {
			pint nxt = make_pair(cur.first + mov.first, cur.second + mov.second);

			if (in_range(nxt) && board[cur.first][cur.second] > board[nxt.first][nxt.second]) {
				dp_cnt[cur.first][cur.second] += dfs(nxt);
			}
		}
	}
	return dp_cnt[cur.first][cur.second];
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> m >> n;
	board = vector<vector<int>>(m, vector<int>(n));
	dp_cnt = vector<vector<int>>(m, vector<int>(n, NOT_VISIT));
	for (vector<int>& line : board) {
		for (int& i : line) {
			cin >> i;
		}
	}

	cout << dfs(make_pair(0, 0));

	return 0;
}