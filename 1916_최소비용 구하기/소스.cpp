#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

const int INF = 1000000000;
const int MAX_NODE = 1001;

vector<int> dist(MAX_NODE, INF);
vector<vector<pint>> graph(MAX_NODE);
priority_queue<pint, vector<pint>, greater<pint>>pq;

int dijkstra(int start, int destination) {
	dist[start] = 0;
	pq.push(make_pair(dist[start], start));

	while (!pq.empty()) {
		int cur = pq.top().second;
		int cur_dist = pq.top().first;
		pq.pop();

		if (dist[cur] >= cur_dist) {
			for (pint& edge : graph[cur]) {
				int nxt = edge.first;
				int new_val = cur_dist + edge.second;

				if (new_val < dist[nxt]) {
					dist[nxt] = new_val;
					pq.push(make_pair(new_val, nxt));
				}
			}
		}
	}

	return dist[destination];
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	for (int i = 0, stt, dst, val; i < m; i++) {
		cin >> stt >> dst >> val;
		graph[stt].push_back(make_pair(dst, val));
	}

	int depart, arrive;
	cin >> depart >> arrive;
	cout << dijkstra(depart, arrive);

	return 0;
}