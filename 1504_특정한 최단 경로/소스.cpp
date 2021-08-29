#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

#define INF 0x7fffFFFF

using namespace std;

typedef pair<int, int> p;
typedef struct NODE {
	NODE() {}
	NODE(int _destination, int _value) : dest(_destination), val(_value) {};
	int dest = 0, val = 0;
}node;

int findPath(vector<vector<node>> &graph, int depart, int arrive) {
	vector<int> distance(graph.size(), INF);
	priority_queue<p, vector<p>, less<p>> pq;
	
	//초기화 아주 중요!!!
	distance[depart] = 0;
	pq.push({ 0, depart });
	while (!pq.empty()) {
		int cur = pq.top().second;
		pq.pop();

		for (uint32_t i = 0; i < graph[cur].size(); i++) {
			int newVal = distance[cur] + graph[cur][i].val;
			int oldVal = distance[graph[cur][i].dest];

			if (newVal < oldVal) {
				distance[graph[cur][i].dest] = newVal;
				pq.push({ newVal, graph[cur][i].dest });
			}
		}
	}

	return distance[arrive];
}

bool hasInfinite(vector<int> &argi) {
	for (uint32_t i = 0; i < argi.size(); i++) {
		if (argi[i] == INF) { return true; }
	}
	return false;
}

int getSum(vector<int> &argi) {
	int sum = 0;
	for (uint32_t i = 0; i < argi.size(); i++) {
		sum += argi[i];
	}
	return sum;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, E = 0;
	cin >> N >> E;
	vector<vector<node>> graph(N);
	for (int i = 0, temp[3]; i < E; i++) {
		cin >> temp[0] >> temp[1] >> temp[2];
		temp[0]--, temp[1]--;
		graph[temp[0]].push_back(node(temp[1], temp[2]));
		graph[temp[1]].push_back(node(temp[0], temp[2]));
	}

	vector<int> checkPoint = {0, 0, 0, N - 1};
	cin >> checkPoint[1] >> checkPoint[2];
	checkPoint[1]--, checkPoint[2]--;

	vector<int> dist1 = {
		findPath(graph, checkPoint[0], checkPoint[1]),
		findPath(graph, checkPoint[1], checkPoint[2]),
		findPath(graph, checkPoint[2], checkPoint[3])
	};
	vector<int> dist2 = {
		findPath(graph, checkPoint[0], checkPoint[2]),
		findPath(graph, checkPoint[2], checkPoint[1]),
		findPath(graph, checkPoint[1], checkPoint[3])
	};

	if (!hasInfinite(dist1) && !hasInfinite(dist2)) {
		cout << min(getSum(dist1), getSum(dist2));
	}
	else if (!hasInfinite(dist1)) {
		cout << getSum(dist1);
	}
	else if (!hasInfinite(dist2)) {
		cout << getSum(dist2);
	}
	else {
		cout << -1;
	}

	return 0;
}