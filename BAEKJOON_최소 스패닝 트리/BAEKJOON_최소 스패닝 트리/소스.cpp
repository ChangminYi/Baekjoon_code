#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

long long prim(vector<vector<pair<int, int>>> &graph) {
	long long ans = 0;
	vector<bool> visit(graph.size(), false);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	pq.push({ 0,0 });
	while (!pq.empty()) {
		int curCost = pq.top().first;
		int curPos = pq.top().second;
		pq.pop();

		if (!visit[curPos]) {
			ans += curCost;
			visit[curPos] = true;

			for (uint32_t i = 0; i < graph[curPos].size(); i++) {
				if (!visit[graph[curPos][i].first]) {
					pq.push({ graph[curPos][i].second, graph[curPos][i].first });
				}
			}
		}
	}

	return ans;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int v = 0, e = 0;
	cin >> v >> e;
	vector<vector<pair<int, int>>> vortex(v);
	for (int i = 0, temp[3]; i < e; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> temp[j];
			if (j != 2) { temp[j]--; }
		}

		vortex[temp[0]].push_back({ temp[1], temp[2] });
		vortex[temp[1]].push_back({ temp[0], temp[2] });
	}

	cout << prim(vortex);

	return 0;
}