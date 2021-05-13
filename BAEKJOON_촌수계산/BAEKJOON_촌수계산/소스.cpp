#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int n = 0, m = 0;
	int start = 0, end = 0;
	cin >> n >> start >> end >> m;
	start--, end--;

	vector<vector<int>> graph(n);
	for (int i = 0, temp[2]; i < m; i++) {
		cin >> temp[0] >> temp[1];
		graph[--temp[0]].push_back(--temp[1]);
		graph[temp[1]].push_back(temp[0]);
	}

	int res = -1;
	vector<bool> visit(n, false);
	queue<pair<int, int>> togo;
	togo.push(make_pair(start, 0));
	while (!togo.empty()) {
		int now = togo.front().first;
		int dist = togo.front().second;
		togo.pop();

		if (now == end) {
			res = dist;
			break;
		}
		else if (!visit[now]) {
			visit[now] = true;

			for (uint32_t i = 0; i < graph[now].size(); i++) {
				if (!visit[graph[now][i]]) {
					togo.push(make_pair(graph[now][i], dist + 1));
				}
			}
		}
	}

	cout << res;

	return 0;
}