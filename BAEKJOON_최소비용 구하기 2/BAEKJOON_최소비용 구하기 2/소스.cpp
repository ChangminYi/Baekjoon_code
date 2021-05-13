#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pint;

class compare {
public:
	bool operator() (pint a, pint b) {
		return a.first > b.first;
	}
};

pair<int, deque<int>> findPath(vector<vector<pint>> &graph, int arrival, int destination) {
	vector<int> costTable(graph.size(), INT32_MAX);
	vector<bool> found(graph.size(), false);
	vector<int> from(graph.size());
	priority_queue<pint, vector<pint>, compare> pq;

	costTable[arrival] = 0;
	found[arrival] = true;
	pq.push(make_pair(0, arrival));
	while (!pq.empty()) {
		int current = pq.top().second;
		pq.pop();

		found[current] = true;
		for (uint32_t i = 0; i < graph[current].size(); i++) {
			int newCost = costTable[current] + graph[current][i].first;
			int oldCost = costTable[graph[current][i].second];

			if (!found[graph[current][i].second]) {
				if (newCost < oldCost) {
					costTable[graph[current][i].second] = newCost;
					from[graph[current][i].second] = current;

					pq.push(make_pair(newCost, graph[current][i].second));
				}
			}
		}
	}

	deque<int> trace(1, destination);
	while (trace.front() != arrival) {
		trace.push_front(from[trace.front()]);
	}

	return make_pair(costTable[destination], trace);
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n = 0, m = 0, arrival = 0, destiation = 0;
	cin >> n >> m;
	vector<vector<pint>> city(n);
	for (int i = 0, arri, dest, val; i < m; i++) {
		cin >> arri >> dest >> val;
		city[--arri].push_back(make_pair(val, --dest));
	}
	cin >> arrival >> destiation;


	pair<int, deque<int>> res = findPath(city, --arrival, --destiation);
	cout << res.first << '\n';
	cout << res.second.size() << '\n';
	for (int i : res.second) {
		cout << i + 1 << ' ';
	}

	return 0;
}