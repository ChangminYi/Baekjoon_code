#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<bool>> board;
vector<vector<int>> dp;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	board = vector<vector<bool>>(n + 1, vector<bool>(m + 1, 0));
	dp = vector<vector<int>>(n + 1, vector<int>(m + 1, false));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char tmp;
			cin >> tmp;
			dp[i][j] = tmp - '0';
			board[i][j] = (tmp == '1' ? true : false);
		}
	}

	int max_len = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (board[i][j]) {
				if (dp[i - 1][j] > 0 && dp[i][j - 1] > 0 && dp[i - 1][j - 1] > 0) {
					if (dp[i - 1][j] > 1 && dp[i][j - 1] > 1 && dp[i - 1][j - 1] > 1) {
						dp[i][j] = min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] }) + 1;
					}
					else {
						dp[i][j] = 2;
					}
				}

				max_len = max(max_len, dp[i][j]);
			}
		}
	}

	cout << max_len * max_len;

	return 0;
}