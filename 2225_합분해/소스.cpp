#include <iostream>
#include <vector>

using namespace std;

const int DIV = 1000000000;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, k;
	cin >> n >> k;

	vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
	for (int i = 0; i <= n; i++) {
		dp[1][i] = 1;
	}
	for (int i = 0; i <= k; i++) {
		dp[i][0] = 1;
	}

	for (int i = 2; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % DIV;
		}
	}

	cout << dp.back().back();

	return 0;
}