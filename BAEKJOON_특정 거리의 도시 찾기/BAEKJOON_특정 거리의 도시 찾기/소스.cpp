#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 2000000000

using namespace std;
typedef pair<int, int> pint;

vector<int> dijk(vector<vector<pint>> &graph, int start, int dist_tofind) {
	priority_queue<pint, vector<pint>, greater<pint>> pq;
	vector<int> dist(graph.size(), INF);
	
	dist[start] = 0;
	pq.push(make_pair(dist[start], start));
	while (!pq.empty()) {
		int cur = pq.top().second;
		pq.pop();

		for (uint32_t i = 0; i < graph[cur].size(); i++) {
			int newDist = dist[cur] + graph[cur][i].second;
			int oldDist = dist[graph[cur][i].first];
			
			if (newDist < oldDist) {
				dist[graph[cur][i].first] = newDist;
				pq.push(make_pair(newDist, graph[cur][i].first));
			}
		}
	}

	vector<int> res;
	for (uint32_t i = 0; i < dist.size(); i++) {
		if (dist[i] == dist_tofind) {
			res.push_back(i + 1);
		}
	}

	return res;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int N = 0, M = 0, K = 0, X = 0;
	cin >> N >> M >> K >> X;
	vector<vector<pint>> graph(N);
	for (int i = 0; i < M; i++) {
		pint temp;
		cin >> temp.first >> temp.second;
		graph[--temp.first].push_back(make_pair(--temp.second, 1));
	}

	vector<int> res = dijk(graph, --X, K);
	if (res.empty()) {
		cout << -1;
	}
	else {
		for (int i : res) {
			cout << i << '\n';
		}
	}

	return 0;
}