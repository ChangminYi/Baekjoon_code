#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	vector<int> degree(n + 1, 0);
	vector<vector<int>> graph(n + 1);
	for (int i = 0, frt, bck; i < m; i++) {
		cin >> frt >> bck;

		degree[bck]++;
		graph[frt].push_back(bck);
	}

	queue<int> que;
	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0) {
			que.push(i);
		}
	}
	while (!que.empty()) {
		int cur = que.front();
		que.pop();
		cout << cur << ' ';

		for (int& i : graph[cur]) {
			degree[i]--;

			if (degree[i] == 0) {
				que.push(i);
			}
		}
	}

	return 0;
}