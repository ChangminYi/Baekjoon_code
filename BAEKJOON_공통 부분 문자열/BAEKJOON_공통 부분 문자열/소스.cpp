#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	string str1, str2;
	cin >> str1 >> str2;

	int res = 0;
	vector<vector<int>> dp(str1.size() + 1, vector<int>(str2.size() + 1, 0));
	for (size_t i = 1; i <= str1.size(); i++) {
		for (int j = 1; j <= str2.size(); j++) {
			if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
				res = max(res, dp[i][j]);
			}
			else {
				dp[i][j] = 0;
			}
		}
	}

	cout << res;

	return 0;
}