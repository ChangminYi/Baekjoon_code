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
	* ���� �ڽ��� ���� �ƴ� ���� ���� dp�� ��
	* ���� ���� ���� �ڽ��� ����ġ�� ���ϸ�
	* ���� ���� dp�� �� �ּҸ� ���� �� ����.
	*/
	for (int i = 1; i <= n; i++) {
		dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + weight[i][0];
		dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + weight[i][1];
		dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + weight[i][2];
	}

	cout << min({ dp[n][0], dp[n][1], dp[n][2] });

	return 0;
}