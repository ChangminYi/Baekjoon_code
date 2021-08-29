#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

vector<pint> arg;
vector<int> dp, mx;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, s;
	cin >> n >> s;

	arg = vector<pint>(n + 1);
	dp = vector<int>(n + 1);
	mx = vector<int>(n + 1);

	for (int i = 1; i <= n; i++) {
		cin >> arg[i].first >> arg[i].second;
	}
	sort(arg.begin(), arg.end());

	for (int i = 1; i <= n; i++) {
		mx[i] = mx[i - 1];
		while (mx[i] < i && arg[i].first - arg[mx[i]].first >= s) {
			mx[i]++;
		}
		mx[i]--;
	}

	for (int i = 1; i <= n; i++) {
		dp[i] = max(dp[i - 1], dp[mx[i]] + arg[i].second);
	}

	cout << dp[n];

	return 0;
}