#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

#define INF 0x7fffFFFF

typedef pair<int, int> pint;
typedef class NODE {
public:
	int destination = 0, cost = 0;
	NODE() {};
	NODE(int _dest, int _cost) :destination(_dest), cost(_cost) {};
} node;

vector<int> findPath(vector<vector<node>> &graph, int start) {
	vector<int> costTable(graph.size(), INF);
	priority_queue<pint, vector<pint>, less<pint>> pq;

	costTable[start] = 0;
	pq.push({ 0, start });
	while (!pq.empty()) {
		int current = pq.top().second;
		pq.pop();

		for (uint32_t i = 0; i < graph[current].size(); i++) {
			int newCost = costTable[current] + graph[current][i].cost;
			int oldCost = costTable[graph[current][i].destination];

			if (newCost < oldCost) {
				costTable[graph[current][i].destination] = newCost;
				pq.push({ newCost, graph[current][i].destination });
			}
		}
	}

	return costTable;
}

void printVector(vector<int> &argi) {
	cout << (argi.front() == INF ? 0 : argi.front());
	for (uint32_t i = 1; i < argi.size(); i++) {
		cout << ' ' << (argi[i] == INF ? 0 : argi[i]);
	}
	cout << '\n';
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, M = 0;
	cin >> N >> M;
	vector<vector<node>> graph(N);
	vector<vector<int>> tempNode(N, vector<int>(N, INF));
	for (int i = 0, temp[3]; i < M; i++) {
		cin >> temp[0] >> temp[1] >> temp[2];
		temp[0]--, temp[1]--;
		tempNode[temp[0]][temp[1]] = min(temp[2], tempNode[temp[0]][temp[1]]);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (tempNode[i][j] != INF) {
				graph[i].push_back(node(j, tempNode[i][j]));
			}
		}
	}

	for (int i = 0; i < N; i++) {
		vector<int> res = findPath(graph, i);
		printVector(res);
	}
	return 0;
}