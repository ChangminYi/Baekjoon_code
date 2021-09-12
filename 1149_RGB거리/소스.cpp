#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int ROW = 3;

int n;
vector<vector<int>> weight, dp;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	weight.resize(n + 1, vector<int>(ROW, 0));
	dp.resize(n + 1, vector<int>(ROW, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < ROW; j++) {
			cin >> weight[i][j];
		}
	}

	/*
	* 현재 자신의 색이 아닌 곳의 이전 dp값 중
	* 가장 작은 값에 자신의 가중치를 더하면
	* 현재 색의 dp값 중 최소를 얻을 수 있음.
	*/
	for (int i = 1; i <= n; i++) {
		dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + weight[i][0];
		dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + weight[i][1];
		dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + weight[i][2];
	}

	cout << min({ dp[n][0], dp[n][1], dp[n][2] });

	return 0;
}