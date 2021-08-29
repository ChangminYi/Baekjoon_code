#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, max_weight;
	cin >> n >> max_weight;
	vector<int> weight(n + 1), value(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> weight[i] >> value[i];
	}

	vector<vector<int>> dp(n + 1, vector<int>(max_weight + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= max_weight; j++) {
			if (j < weight[i]) {
				dp[i][j] = dp[i - 1][j];
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
			}
		}
	}

	cout << dp.back().back();

	return 0;
}