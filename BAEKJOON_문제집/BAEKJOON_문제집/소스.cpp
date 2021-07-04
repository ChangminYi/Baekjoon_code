#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

vector<int> degree;
vector<vector<int>> graph;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	graph = vector<vector<int>>(n + 1);
	degree = vector<int>(n + 1, 0);
	for (int i = 0; i < m;i++) {
		pint tmp;
		cin >> tmp.first >> tmp.second;
		graph[tmp.first].push_back(tmp.second);
		degree[tmp.second]++;
	}

	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0) {
			pq.push(i);
		}
	}
	while (!pq.empty()) {
		int cur = pq.top();
		cout << cur << ' ';
		pq.pop();

		for (int& i : graph[cur]) {
			degree[i]--;

			if (degree[i] == 0) {
				pq.push(i);
			}
		}
	}

	return 0;
}