#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <functional>

#define INF 1000000000
#define START 0

using namespace std;

typedef pair<int, int> pint;

list<pint> dijk(const vector<vector<pint>> &graph) {
	//{distance, from}
	vector<pint> dist(graph.size(), make_pair(INF, -1));
	//{val, now}
	priority_queue<pint, vector<pint>, greater<pint>> pq;

	dist.front() = make_pair(0, -1);
	pq.push(make_pair(0, START));
	while (!pq.empty()) {
		int cur = pq.top().second;
		pq.pop();

		for (uint32_t i = 0; i < graph[cur].size(); i++) {
			int newVal = dist[cur].first + graph[cur][i].second;
			int oldVal = dist[graph[cur][i].first].first;

			if (newVal < oldVal) {
				dist[graph[cur][i].first].first = newVal;
				dist[graph[cur][i].first].second = cur;

				pq.push(make_pair(newVal, graph[cur][i].first));
			}
		}
	}

	list<pint> nodeSet;
	vector<bool> visit(graph.size(), false);
	queue<int> togo;
	togo.push(START);
	while (!togo.empty()) {
		int cur = togo.front();
		visit[cur] = true;
		togo.pop();

		for (uint32_t i = 0; i < graph[cur].size(); i++) {
			if (cur == dist[graph[cur][i].first].second && !visit[graph[cur][i].first]) {
				nodeSet.push_back(make_pair(cur + 1, graph[cur][i].first + 1));
				togo.push(graph[cur][i].first);
			}
		}
	}

	return nodeSet;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int N = 0, M = 0;
	cin >> N >> M;
	vector<vector<pint>> graph(N);
	for (int i = 0; i < M; i++) {
		pint temp;
		int temp_val;
		cin >> temp.first >> temp.second>>temp_val;
		graph[--temp.first].push_back(make_pair(--temp.second, temp_val));
		graph[temp.second].push_back(make_pair(temp.first, temp_val));
	}

	list<pint> set = dijk(graph);
	cout << set.size() << '\n';
	for (pint &p : set) {
		cout << p.first << ' ' << p.second << '\n';
	}

	return 0;
}
