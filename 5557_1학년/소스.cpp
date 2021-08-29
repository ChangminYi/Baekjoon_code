#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;
const int MAX = 21;

int n;
vector<int> argi;
vector<vector<lli>> dp;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n, right_val;
	cin >> n;
	n--;
	argi = vector<int>(n);
	dp = vector<vector<lli>>(n, vector<lli>(MAX, 0));
	for (int& i : argi) {
		cin >> i;
	}
	cin >> right_val;

	dp.front()[argi.front()] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < MAX; j++) {
			if (0 <= j + argi[i] && j + argi[i] < MAX) {
				dp[i][j + argi[i]] += dp[i - 1][j];
			}
			if (0 <= j - argi[i] && 0 <= j - argi[i] < 20) {
				dp[i][j - argi[i]] += dp[i - 1][j];
			}
		}
	}

	cout << dp.back()[right_val];

	return 0;
}