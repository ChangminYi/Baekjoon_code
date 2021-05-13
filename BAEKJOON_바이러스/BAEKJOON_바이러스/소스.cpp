#include <iostream>
#include <deque>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int n_node = 0, n_edge = 0;
	cin >> n_node >> n_edge;

	deque<deque<int>> graph(n_node);
	for (int i = 0, temp[2]; i < n_edge; i++) {
		cin >> temp[0] >> temp[1];
		graph[--temp[0]].push_back(--temp[1]);
		graph[temp[1]].push_back(temp[0]);
	}

	int cnt = -1;
	deque<bool> check(n_node, false);
	queue<int> togo;
	togo.push(0);
	while (!togo.empty()) {
		int cur = togo.front();
		togo.pop();

		if (!check[cur]) {
			check[cur] = true;
			cnt++;

			for (uint32_t i = 0; i < graph[cur].size(); i++) {
				togo.push(graph[cur][i]);
			}
		}
	}

	cout << cnt;

	return 0;
}