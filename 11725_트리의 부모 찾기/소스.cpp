#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int N = 0;
	cin >> N;
	vector<vector<int>> graph(N + 1);
	for (int i = 0, temp[2]; i < N - 1; i++) {
		cin >> temp[0] >> temp[1];
		graph[temp[0]].push_back(temp[1]);
		graph[temp[1]].push_back(temp[0]);
	}

	vector<int> parent(N + 1, 0);
	vector<bool> visit(N + 1, false);

	queue<int> toGo;
	toGo.push(1);
	while (!toGo.empty()) {
		int current = toGo.front();
		visit[current] = true;
		toGo.pop();

		for (uint32_t i = 0; i < graph[current].size(); i++) {
			if (!visit[graph[current][i]]) {
				parent[graph[current][i]] = current;
				toGo.push(graph[current][i]);
			}
		}
	}

	for (int i = 2; i <= N; i++) {
		cout << parent[i] << '\n';
	}

	return 0;
}