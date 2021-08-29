#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> pint;
class edge {
public:
	int adj_node = 0;
	int weight = 0;
	edge(int _adj, int _w) : adj_node(_adj), weight(_w) {}
};

int n, m;
uint32_t k;
vector<vector<edge>> graph;
vector<priority_queue<int>> pq_set;

void dijkstra(int start) {
	priority_queue<pint, vector<pint>, greater<pint>> pq;
	pq.push(make_pair(0, start));
	pq_set[start].push(0);

	while (!pq.empty()) {
		int cur = pq.top().second;
		int cur_dist = pq.top().first;
		pq.pop();

		for (const edge& e : graph[cur]) {
			int nxt = e.adj_node;
			int new_dist = cur_dist + e.weight;

			if (pq_set[nxt].size() < k) {
				pq_set[nxt].push(new_dist);
				pq.push(make_pair(new_dist, nxt));
			}
			else if (pq_set[nxt].top() > new_dist) {
				pq_set[nxt].pop();
				pq_set[nxt].push(new_dist);
				pq.push(make_pair(new_dist, nxt));
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m >> k;
	graph = vector<vector<edge>>(n + 1);
	pq_set = vector<priority_queue<int>>(n + 1);
	for (int i = 0, arg1, arg2, wei; i < m; i++) {
		cin >> arg1 >> arg2 >> wei;
		graph[arg1].push_back(edge(arg2, wei));
	}

	dijkstra(1);
	for (int i = 1; i <= n; i++) {
		cout << (pq_set[i].size() == k ? pq_set[i].top() : -1) << '\n';
	}

	return 0;
}