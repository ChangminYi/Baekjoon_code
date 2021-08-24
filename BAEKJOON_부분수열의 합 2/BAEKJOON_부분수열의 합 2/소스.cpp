#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef long long lli;

int n, s;
lli ans = 0;
vector<int> argi;
unordered_map<int, int> cnt;

void dfs(int cur, int sum, bool left) {
	if (left) {
		if (cur == n / 2) {
			cnt[sum]++;
			return;
		}
	}
	else {
		if (cur == n) {
			ans += cnt[s - sum];
			return;
		}
	}

	dfs(cur + 1, sum, left);
	dfs(cur + 1, sum + argi[cur], left);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> s;
	argi.resize(n);
	for (int& i : argi) {
		cin >> i;
	}

	dfs(0, 0, true);
	dfs(n / 2, 0, false);

	cout << (s == 0 ? ans - 1 : ans);

	return 0;
}