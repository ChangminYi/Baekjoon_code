#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n = 0, m = 0, cost_sum = 0;
vector<int> mem_size, cost;
vector<vector<int>> dp;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	mem_size = vector<int>(n + 1);
	cost = vector<int>(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> mem_size[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> cost[i];
		cost_sum += cost[i];
	}

	dp = vector<vector<int>>(n + 1, vector<int>(cost_sum + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= cost_sum; j++) {
			if (j - cost[i] >= 0) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - cost[i]] + mem_size[i]);
			}
			dp[i][j] = max(dp[i][j], dp[i - 1][j]);
		}
	}

	for (int i = 0; i <= cost_sum; i++) {
		if (dp[n][i] >= m) {
			cout << i;
			break;
		}
	}

	return 0;
}