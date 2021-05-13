#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

typedef struct COORDINATE {
	int x, y, z;
}cor;

int distance(const cor &a, const cor &b) {
	return min(abs(a.x - b.x), min(abs(a.y - b.y), abs(a.z - b.z)));
}

long long prim(vector<cor> &graph) {
	long long sum = 0;
	vector<bool> visit(graph.size(), false);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	pq.push({ 0, 0 });
	while (!pq.empty()) {
		int curCost = pq.top().first;
		int curPos = pq.top().second;
		pq.pop();

		if (!visit[curPos]) {
			sum += curCost;
			visit[curPos] = true;

			for (uint32_t i = 0; i < graph.size(); i++) {
				if (!visit[i]) {
					pq.push({distance(graph[curPos], graph[i]), i});
				}
			}
		}
	}

	return sum;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int n = 0;
	cin >> n;
	vector<cor> planet(n);
	for (cor &i : planet) {
		cin >> i.x >> i.y >> i.z;
	}

	cout << prim(planet);

	return 0;
}