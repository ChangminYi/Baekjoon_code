#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>

using namespace std;

typedef unsigned int uint;

vector<vector<uint>> getTime(vector<vector<pair<int, int>>> &graph) {
	vector<vector<uint>> dist(graph.size(), vector<uint>(graph.size(), INT_MAX));
	
	for (uint32_t i = 0; i < dist.size(); i++) {
		priority_queue<pair<uint, int>, vector<pair<uint, int>>, greater<pair<uint, int>>> pq;

		dist[i][i] = 0;
		pq.push(make_pair(0, i));
		while (!pq.empty()) {
			int cur = pq.top().second;
			pq.pop();

			for (uint32_t j = 0; j < graph[cur].size(); j++) {
				int newVal = dist[i][cur] + graph[cur][j].second;
				int oldVal = dist[i][graph[cur][j].first];

				if (newVal < oldVal) {
					dist[i][graph[cur][j].first] = newVal;
					pq.push(make_pair(newVal, graph[cur][j].first));
				}
			}
		}

	}
	return dist;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, M = 0, X = 0;
	cin >> N >> M >> X;
	X--;

	vector<vector<pair<int, int>>> graph(N);
	for (int i = 0, st, en, co; i < M; i++) {
		cin >> st >> en >> co;
		graph[--st].push_back(make_pair(--en, co));
	}

	vector<vector<uint>> time = getTime(graph);
	unsigned int maxSum = 0;
	for (int i = 0; i < N; i++) {
		maxSum = max(maxSum, time[i][X] + time[X][i]);
	}

	cout << maxSum;

	return 0;
}