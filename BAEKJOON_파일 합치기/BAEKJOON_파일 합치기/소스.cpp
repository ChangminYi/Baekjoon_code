#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int testcase;
	cin >> testcase;
	do {
		int n;
		cin >> n;

		vector<int> cost(n + 1), acc_sum(n + 1);
		vector<vector<int>> dp(n + 1, vector<int>(n + 1));
		for (int i = 1; i <= n; i++) {
			cin >> cost[i];
			acc_sum[i] = acc_sum[i - 1] + cost[i];
		}

		for (int i = 1; i < n; i++) {
			for (int j = 1; i + j <= n; j++) {
				int t_col = i + j;
				dp[j][t_col] = INT32_MAX;

				for (int k = j; k < t_col; k++) {
					dp[j][t_col] = min(
						dp[j][t_col],
						dp[j][k] + dp[k + 1][t_col] + acc_sum[t_col] - acc_sum[j - 1]
					);
				}
			}
		}

		cout << dp[1][n] << '\n';
	} while (--testcase > 0);

	return 0;
}