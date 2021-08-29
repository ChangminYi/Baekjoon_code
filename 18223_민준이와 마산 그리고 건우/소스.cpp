#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <functional>

using namespace std;
typedef pair<int, int> pint;

const int MAX = 100000000;
vector<vector<pint>> graph;

int dijk(int start, int desti) {
	vector<int> dist(graph.size(), MAX);
	priority_queue<pint, vector<pint>, greater<pint>> pq;

	dist[start] = 0;
	pq.push(make_pair(0, start));
	while (!pq.empty()) {
		int cur = pq.top().second;
		pq.pop();

		for (uint32_t i = 0; i < graph[cur].size(); i++) {
			int new_val = dist[cur] + graph[cur][i].second;
			int old_val = dist[graph[cur][i].first];

			if (new_val < old_val) {
				dist[graph[cur][i].first] = new_val;
				pq.push(make_pair(new_val, graph[cur][i].first));
			}
		}
	}

	return dist[desti];
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n_node, n_edge, p;
	cin >> n_node >> n_edge >> p;
	graph = vector<vector<pint>>(n_node + 1);
	for (int i = 0; i < n_edge; i++) {
		pint tmp;
		int tmp_val;
		cin >> tmp.first >> tmp.second >> tmp_val;

		graph[tmp.first].push_back(make_pair(tmp.second, tmp_val));
		graph[tmp.second].push_back(make_pair(tmp.first, tmp_val));
	}

	int straight = dijk(1, n_node);
	int saving = dijk(1, p) + dijk(p, n_node);

	if (straight == saving) {
		cout << "SAVE HIM";
	}
	else {
		cout << "GOOD BYE";
	}

	return 0;
}