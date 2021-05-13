#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

#define INF 2000000000

using namespace std;
typedef pair<int, int> pint;

pint dijk(const vector<vector<pint>> &graph, const int start) {
	vector<int> dist(graph.size(), INF);
	priority_queue<pint, vector<pint>, greater<pint>> pq;

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

	pint res = { 0, -1 };
	for (uint32_t i = 0; i < dist.size(); i++) {
		if (dist[i] != INF) {
			res.first++;
			res.second = max(res.second, dist[i]);
		}
	}

	return res;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int testcase = 0;
	cin >> testcase;
	for (; testcase > 0; testcase--) {
		int n = 0, d = 0, c = 0;
		cin >> n >> d >> c;
		c--;
		vector<vector<pint>> graph(n);
		for (int i = 0; i < d; i++) {
			int a = 0, b = 0, s = 0;
			cin >> a >> b >> s;
			a--, b--;
			graph[b].push_back(make_pair(a, s));
		}

		pint res = dijk(graph, c);
		cout << res.first << ' ' << res.second << '\n';

	}

	return 0;
}