#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> weight(3), max_dp(3), min_dp(3);

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	for (int i = 0; i < 3; i++) {
		cin >> max_dp[i];
		min_dp[i] = max_dp[i];
	}

	/*
	* 1번 dp값을 먼저 갱신하면 2번 갱신에서 꼬이기 때문에
	* 0번, 2번을 저장해 두었다가 가장 마지막에 갱신
	*/
	for (int i = 1, tmp0, tmp2; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> weight[j];
		}

		// max값 갱신
		tmp0 = max_dp[0], tmp2 = max_dp[2];
		max_dp[0] = max(max_dp[0], max_dp[1]) + weight[0];
		max_dp[2] = max(max_dp[1], max_dp[2]) + weight[2];
		max_dp[1] = max({ tmp0, max_dp[1], tmp2 }) + weight[1];

		//min값 갱신
		tmp0 = min_dp[0], tmp2 = min_dp[2];
		min_dp[0] = min(min_dp[0], min_dp[1]) + weight[0];
		min_dp[2] = min(min_dp[1], min_dp[2]) + weight[2];
		min_dp[1] = min({ tmp0, min_dp[1], tmp2 }) + weight[1];
	}

	cout << max({ max_dp[0], max_dp[1], max_dp[2] }) << ' ' << min({ min_dp[0], min_dp[1], min_dp[2] });

	return 0;
}