#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int NOT_VISIT = -1;
const int NOT_ADOPTER = 0;
const int EARLY_ADOPTER = 1;

vector<vector<int>> graph, tree;
vector<vector<int>> dp;

int dfs(int root, int state) {
    if (dp[root][state] == NOT_VISIT) {
		dp[root][state] = state;

		switch (state) {
		case NOT_ADOPTER:
			for (int nxt : tree[root]) {
				dp[root][state] += dfs(nxt, EARLY_ADOPTER);
			}
			break;
		case EARLY_ADOPTER:
			for (int nxt : tree[root]) {
				dp[root][state] += min(dfs(nxt, NOT_ADOPTER), dfs(nxt, EARLY_ADOPTER));
			}
			break;
		}
    }

	return dp[root][state];
}

void init_tree(int root, int parent) {
	for (int nxt : graph[root]) {
		if (nxt != parent) {
			tree[root].push_back(nxt);
			init_tree(nxt, root);
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	graph = vector<vector<int>>(n + 1, vector<int>());
	tree = vector<vector<int>>(n + 1, vector<int>());
	dp = vector<vector<int>>(n + 1, vector<int>(2, NOT_VISIT));
	for (int i = 0, arg1, arg2; i < n - 1; i++) {
		cin >> arg1 >> arg2;
		graph[arg1].push_back(arg2);
		graph[arg2].push_back(arg1);
	}
	init_tree(1, 0);

	cout << min(dfs(1, NOT_ADOPTER), dfs(1, EARLY_ADOPTER));

	return 0;
}