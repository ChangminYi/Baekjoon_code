#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

const int NUM_MAX = 10;
const int VISIT_MAX = 1 << NUM_MAX;
const int MOD = 1000000000;

int n;
lli ans = 0;
vector<vector<vector<lli>>> dp;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	dp = vector<vector<vector<lli>>>(n + 1, vector<vector<lli>>(NUM_MAX, vector<lli>(VISIT_MAX, 0)));

	for (int i = 1; i < NUM_MAX; i++) {
		dp[1][i][1 << i] = 1;
	}
	
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < NUM_MAX; j++) {
			for (int k = 0; k < VISIT_MAX; k++) {
				lli& cur = dp[i][j][k | (1 << j)];

				if (j > 0) {
					cur += dp[i - 1][j - 1][k];
				}
				if (j < NUM_MAX - 1) {
					cur += dp[i - 1][j + 1][k];
				}

				cur %= MOD;
			}
		}
	}

	for (int i = 0; i < NUM_MAX; i++) {
		ans += dp[n][i][VISIT_MAX - 1];
	}

	cout << ans % MOD;

	return 0;
}