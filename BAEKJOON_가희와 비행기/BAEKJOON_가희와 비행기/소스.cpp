#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

const int MAX_SIZE = 4001;
int n;
lli DIV;
vector<vector<lli>> dp = vector<vector<lli>>(MAX_SIZE, vector<lli>(MAX_SIZE, -1));

lli dfs(int r, int c) {
	if (0 < r && r < n && c <= 0) {
		return 0;
	}
	else if (r == n) {
		return (c == 0 ? 1 : 0);
	}
	else {
		if (dp[r][c] == -1) {
			dp[r][c] = (dfs(r + 1, c + 1) + dfs(r + 1, c - 1)) % DIV;
		}
		return dp[r][c];
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> n >> DIV;
	
	if (n & 1) {
		cout << 0;
	}
	else {
		cout << dfs(0, 0);
	}

	return 0;
}