#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

class edge {
public:
	int adj_node = 0;
	int weight = 0;
	edge() {}
	edge(int _n, int _w) : adj_node(_n), weight(_w) {}
};

int n, m, max_size;
vector<vector<edge>> tree;
vector<int> depth;
vector<int> dist;
vector<bool> visit;
vector<vector<int>> dp;

void dfs(int cur, int cur_dep, int cur_dist) {
	depth[cur] = cur_dep;
	dist[cur] = cur_dist;
	for (const edge& e : tree[cur]) {
		if (!visit[e.adj_node]) {
			visit[e.adj_node] = true;
			dp[e.adj_node][0] = cur;
			dfs(e.adj_node, cur_dep + 1, cur_dist + e.weight);
		}
	}
}

int lca(int n1, int n2) {
	if (depth[n1] > depth[n2]) {
		swap(n1, n2);
	}

	int diff = depth[n2] - depth[n1];
	for (int i = 0; diff > 0; i++) {
		if (diff % 2 == 1) {
			n2 = dp[n2][i];
		}
		diff /= 2;
	}

	if (n1 == n2) {
		return n1;
	}
	else {
		for (int i = max_size - 1; i >= 0; i--) {
			if (dp[n1][i] != dp[n2][i]) {
				n1 = dp[n1][i];
				n2 = dp[n2][i];
			}
		}

		return dp[n1][0];
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	max_size = (int)log2(n) + 1;
	tree = vector<vector<edge>>(n + 1);
	visit = vector<bool>(n + 1, false);
	depth = vector<int>(n + 1, 0);
	dist = vector<int>(n + 1, 0);
	dp = vector<vector<int>>(n + 1, vector<int>(max_size, 0));
	for (int i = 0, arg1, arg2, val; i < n - 1; i++) {
		cin >> arg1 >> arg2 >> val;
		tree[arg1].push_back(edge(arg2, val));
		tree[arg2].push_back(edge(arg1, val));
	}

	visit[1] = true;
	dfs(1, depth[1] = 1, dist[1] = 0);
	for (int j = 1; j < max_size; j++) {
		for (int i = 1; i <= n; i++) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
	}

	cin >> m;
	do {
		int arg1, arg2;
		cin >> arg1 >> arg2;

		cout << dist[arg1] + dist[arg2] - 2 * dist[lca(arg1, arg2)] << '\n';
	} while (--m > 0);

	return 0;
}