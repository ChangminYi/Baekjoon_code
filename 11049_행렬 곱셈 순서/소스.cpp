#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

int n;
vector<pint> arrs;
vector<vector<int>> dp;

istream& operator>> (istream& in, pint& p) {
	return in >> p.first >> p.second;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	arrs = vector<pint>(n);
	dp = vector<vector<int>>(n, vector<int>(n, 0));
	for (pint& p : arrs) {
		cin >> p;
	}

	for (int i = 0; i < n - 1; i++) {
		dp[i][i + 1] = arrs[i].first * arrs[i + 1].first * arrs[i + 1].second;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			for (int k = j, tmp; k < i + j; k++) {
				tmp = dp[j][k] + dp[k + 1][i + j] + arrs[j].first * arrs[k + 1].first * arrs[i + j].second;				
				dp[j][i + j] = (dp[j][i + j] == 0 ? tmp : min(dp[j][i + j], tmp));
			}
		}
	}

	cout << dp.front().back();
	
	return 0;
}