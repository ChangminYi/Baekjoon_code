#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, max_time = 0;
	cin >> n;
	vector<int> time_spend(n + 1);
	vector<int> degree(n + 1);
	vector<int> dp(n + 1, 0);
	vector<vector<int>> graph(n + 1);
	queue<int> que;
	for (int i = 1, time, child_num, child; i <= n; i++) {
		cin >> time >> child_num;
		time_spend[i] = time;
		dp[i] = time;
		max_time = max(max_time, time);
		if (child_num == 0) {
			que.push(i);
		}
		else {
			for (int j = 0; j < child_num; j++) {
				cin >> child;
				degree[i] = child_num;
				graph[child].push_back(i);
			}
		}
	}

	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		for (int& nxt : graph[cur]) {
			dp[nxt] = max(dp[nxt], dp[cur] + time_spend[nxt]);
			max_time = max(dp[nxt], max_time);
			if (--degree[nxt] == 0) {
				que.push(nxt);
			}
		}
	}

	cout << max_time;

	return 0;
}