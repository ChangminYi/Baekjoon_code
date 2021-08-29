#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int INF = INT32_MAX / 2;
const int NOT_VISIT = -1;
const int CANNOT_GO = 0;

int n;
vector<vector<int>> cost;
vector<vector<int>> dp;

bool has_visited(int a, int b) {
	return a & b;
}

int tsp(int cur, int visit) {
	if (dp[cur][visit] == NOT_VISIT) {
		if (visit == (1 << n) - 1) {
			if (cost[cur][0] != CANNOT_GO) {
				return cost[cur][0];
			}
			else {
				return INF;
			}
		}
		else {
			dp[cur][visit] = INF;

			for (int i = 0; i < n; i++) {
				if (!has_visited(visit, 1 << i) && cost[cur][i] != CANNOT_GO) {
					dp[cur][visit] = min(dp[cur][visit], tsp(i, visit | (1 << i)) + cost[cur][i]);
				}
			}
		}
	}

	return dp[cur][visit];
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	cost = vector<vector<int>>(n, vector<int>(n));
	dp = vector<vector<int>>(n, vector<int>(1 << n, NOT_VISIT));
	for (vector<int>& row : cost) {
		for (int& i : row) {
			cin >> i;
		}
	}

	cout << tsp(0, 1);

	return 0;
}