#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int MAX = 3;
const int INF = INT32_MAX / 2;

int n;
vector<vector<int>> argi, dp;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	argi.resize(n + 1, vector<int>(MAX));
	dp.resize(n + 1, vector<int>(MAX, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < MAX; j++) {
			cin >> argi[i][j];
		}
	}

	/*
	* 1���� n�� ���� �̿��̹Ƿ�,
	* 1�� ���� ���� ���� �ϳ��� �������Ѽ� dp���� ���ϰ�,
	* �� �߿��� �ּڰ��� ����.
	*/
	int res = INF;
	for (int iter = 0; iter < MAX; iter++) {
		for (int i = 0; i < MAX; i++) {
			dp[1][i] = (i == iter ? argi[1][i] : INF);
		}

		for (int i = 2; i <= n; i++) {
			dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + argi[i][0];
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + argi[i][1];
			dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + argi[i][2];
		}

		for (int i = 0; i < MAX; i++) {
			if (i != iter) {
				res = min(res, dp[n][i]);
			}
		}
	}

	cout << res;

	return 0;
}