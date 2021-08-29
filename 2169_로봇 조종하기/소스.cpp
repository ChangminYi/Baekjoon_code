#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef pair<int, int> pint;

const int LEFT = 0;
const int RIGHT = 1;

int n, m;
vector<vector<int>> board, dp;
vector<vector<vector<int>>> tmp;

bool in_range(const int x, const int y) {
	return ((0 <= x && x < n) && (0 <= y && y < m));
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;

	board.resize(n, vector<int>(m));
	dp.resize(n, vector<int>(m));
	tmp.resize(n, vector<vector<int>>(m, vector<int>(2)));

	for (vector<int>& row : board) {
		for (int& i : row) {
			cin >> i;
		}
	}

	dp[0][0] = board[0][0];
	for (int i = 1; i < m; i++) {
		dp[0][i] = dp[0][i - 1] + board[0][i];
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tmp[i][j][RIGHT] = tmp[i][j][LEFT] = dp[i - 1][j] + board[i][j];
		}
		for (int j = 1; j < m; j++) {
			tmp[i][j][LEFT] = max(tmp[i][j][LEFT], tmp[i][j - 1][LEFT] + board[i][j]);
		}
		for (int j = m - 2; j >= 0; j--) {
			tmp[i][j][RIGHT] = max(tmp[i][j][RIGHT], tmp[i][j + 1][RIGHT] + board[i][j]);
		}

		for (int j = 0; j < m; j++) {
			dp[i][j] = max(tmp[i][j][LEFT], tmp[i][j][RIGHT]);
		}
	}

	cout << dp[n - 1][m - 1];

	return 0;
}