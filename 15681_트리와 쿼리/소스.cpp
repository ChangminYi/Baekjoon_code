#include <iostream>
#include <vector>

using namespace std;

int n, r, q;
vector<vector<int>> tree;
vector<bool> visit;
vector<int> dp;

int dfs(int cur) {
	if (tree[cur].size() == 1 && visit[tree[cur][0]]) {
		return dp[cur];
	}
	else {
		for (int& child : tree[cur]) {
			if (!visit[child]) {
				visit[child] = true;
				dp[cur] += dfs(child);
			}
		}

		return dp[cur];
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> r >> q;

	tree.resize(n + 1);
	dp.resize(n + 1, 1);
	visit.resize(n + 1, false);

	for (int i = 0, arg1, arg2; i < n - 1; i++) {
		cin >> arg1 >> arg2;
		tree[arg1].push_back(arg2);
		tree[arg2].push_back(arg1);
	}

	visit[r] = true;
	dfs(r);

	do {
		int subroot;
		cin >> subroot;

		cout << dp[subroot] << '\n';
	} while (--q > 0);

	return 0;
}