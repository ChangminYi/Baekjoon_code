#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

queue<int> getRange(vector<vector<pair<int, int>>> &graph, int start, int searchLimit) {
	vector<unsigned int> dist(graph.size(), INT_MAX);
	priority_queue<pair<unsigned int, int>> pq;
	
	dist[start] = 0;
	pq.push(make_pair(0, start));
	while (!pq.empty()) {
		int cur = pq.top().second;
		unsigned int cost = pq.top().first;
		pq.pop();

		for (uint32_t i = 0; i < graph[cur].size(); i++) {
			unsigned int newVal = dist[cur] + graph[cur][i].second;
			unsigned int oldVal = dist[graph[cur][i].first];

			if (newVal < oldVal) {
				dist[graph[cur][i].first] = newVal;
				pq.push(make_pair(newVal, graph[cur][i].first));
			}
		}
	}

	queue<int> lessThanLimit;
	for (uint32_t i = 0; i < dist.size(); i++) {
		if (dist[i] <= searchLimit) {
			lessThanLimit.push(i);
		}
	}

	return lessThanLimit;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int n = 0, m = 0, r = 0;
	cin >> n >> m >> r;

	vector<vector<pair<int, int>>> graph(n);
	vector<int> item(n);
	for (int &i : item) {
		cin >> i;
	}
	for (int i = 0, temp[3]; i < r; i++) {
		cin >> temp[0] >> temp[1] >> temp[2];
		graph[--temp[0]].push_back(make_pair(--temp[1], temp[2]));
		graph[temp[1]].push_back(make_pair(temp[0], temp[2]));
	}

	int maxVal = 0;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		queue<int> addInd = getRange(graph, i, m);
		while (!addInd.empty()) {
			temp += item[addInd.front()];
			addInd.pop();
		}
		maxVal = max(temp, maxVal);
	}

	cout << maxVal;

	return 0;
}