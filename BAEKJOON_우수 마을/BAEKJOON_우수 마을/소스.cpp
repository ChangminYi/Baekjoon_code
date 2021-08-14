#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int ROOT = 1;
const int USED = 0;
const int NOT_USED = 1;

int n;
vector<int> people;
vector<vector<int>> tree;
vector<vector<int>> dp;

void dfs(int cur, int bef) {
	for (int& nxt : tree[cur]) {
		if (nxt != bef) {
			dfs(nxt, cur);

			dp[USED][cur] += dp[NOT_USED][nxt];
			dp[NOT_USED][cur] += max(dp[USED][nxt], dp[NOT_USED][nxt]);
		}
	}

	dp[USED][cur] += people[cur];
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	people = vector<int>(n + 1, 0);
	tree = vector<vector<int>>(n + 1);
	dp = vector<vector<int>>(2, vector<int>(n + 1, 0));
	for (int i = 1; i <= n; i++) {
		cin >> people[i];
	}
	for (int i = 0, arg1, arg2; i < n - 1; i++) {
		cin >> arg1 >> arg2;
		tree[arg1].push_back(arg2);
		tree[arg2].push_back(arg1);
	}

	dfs(ROOT, 0);
	cout << max(dp[USED][ROOT], dp[NOT_USED][ROOT]);

	return 0;
}