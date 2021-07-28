#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	string str1, str2, str3;
	cin >> str1 >> str2 >> str3;
	vector<vector<vector<int>>> dp(str1.length() + 1, vector<vector<int>>(str2.length() + 1, vector<int>(str3.length() + 1, 0)));

	for (size_t i = 1; i <= str1.length(); i++) {
		for (size_t j = 1; j <= str2.length(); j++) {
			for (size_t k = 1; k <= str3.length(); k++) {
				if (str1[i - 1] == str2[j - 1] && str2[j - 1] == str3[k - 1]) {
					dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
				}
				else {
					dp[i][j][k] = max({ dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1] });
				}
			}
		}
	}

	cout << dp.back().back().back();

	return 0;
}