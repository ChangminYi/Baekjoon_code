#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <functional>

using namespace std;

typedef struct EDGE {
public:
	EDGE() :dest(0), val(0) {};
	EDGE(int _dest, int _val) :dest(_dest), val(_val) {};
	int dest;
	int val;
}edge;

int findPath(int from, int to, vector<deque<edge>> &graph) {
	vector<int> distance = vector<int>(graph.size(), 0x7fffffff);
	priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> pq;
	
	distance[from] = 0;
	pq.push({ distance[from], from });
	while (!pq.empty()) {
		int current = pq.top().second;
		int cost = pq.top().first;
		pq.pop();

		for (uint32_t i = 0; i < graph[current].size(); i++) {
			int newVal = distance[current] + graph[current][i].val;
			int oldVal = distance[graph[current][i].dest];

			if (newVal < oldVal) {
				distance[graph[current][i].dest] = newVal;
				pq.push({ newVal, graph[current][i].dest });
			}
		}
	}

	return distance[to];
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, M = 0, start = 0, end = 0;
	cin >> N >> M;
	vector<deque<edge>> graph = vector<deque<edge>>(N);
	for (int i = 0, temp[3]; i < M; i++) {
		cin >> temp[0] >> temp[1] >> temp[2];
		temp[0]--, temp[1]--;
		graph[temp[0]].push_back(edge(temp[1], temp[2]));
	}
	cin >> start >> end;
	start--, end--;

	cout << findPath(start, end, graph);

	return 0;
}