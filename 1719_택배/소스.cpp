#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct edge {
	int next_node;
	int weight;
	edge(int _node, int _weight) : next_node(_node), weight(_weight) {}
};
struct pq_node {
	int node;
	int dist;
	pq_node(int _node, int _dist) : node(_node), dist(_dist) {}
};
const int INF = INT32_MAX / 2;
const int NO_PARENT = 0;

int n, m;
vector<vector<edge>> graph;
vector<int> parent;
vector<int> dist;
priority_queue<pq_node, vector<pq_node>, greater<pq_node>> pq;

bool operator>(const pq_node& lhs, const pq_node& rhs) {
	return lhs.dist > rhs.dist;
}

void dijk(int start) {
	fill(dist.begin(), dist.end(), INF);
	fill(parent.begin(), parent.end(), NO_PARENT);

	dist[start] = 0;
	pq.push(pq_node(start, 0));
	while (!pq.empty()) {
		int cur = pq.top().node;
		int cur_dist = pq.top().dist;
		pq.pop();

		if (cur_dist <= dist[cur]) {
			for (const edge& e : graph[cur]) {
				int new_dist = cur_dist + e.weight;
				int old_dist = dist[e.next_node];

				if (new_dist < old_dist) {
					dist[e.next_node] = new_dist;
					parent[e.next_node] = (parent[cur] == NO_PARENT ? e.next_node : parent[cur]);
					pq.push(pq_node(e.next_node, new_dist));
				}
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	
	graph.resize(n + 1);
	parent.resize(n + 1);
	dist.resize(n + 1);
	for (int i = 0, arg1, arg2, arg3; i < m; i++) {
		cin >> arg1 >> arg2 >> arg3;
		graph[arg1].push_back(edge(arg2, arg3));
		graph[arg2].push_back(edge(arg1, arg3));
	}

	for (int i = 1; i <= n; i++) {
		dijk(i);

		for (int j = 1; j <= n; j++) {
			i == j ? cout << "- " : cout << parent[j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}