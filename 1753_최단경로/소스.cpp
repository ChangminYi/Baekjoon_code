// 전역변수에서 지역변수로 바꾸니 시간초과.
// 백준 사용할 때는 전역변수 사용이 좋을 듯.

#include <iostream>
#include <vector>
#include <queue>

#define INF 0xFFFFFFFF

using namespace std;

typedef struct NODE {
	unsigned int end;
	unsigned int val;
}node;

void dijkstra(vector<vector<node>> &graph, vector<unsigned int> &dist, unsigned int startpoint) {
	priority_queue<pair<unsigned int, unsigned int>> pq;
	pq.push({0, startpoint});

	while (!pq.empty()) {
		unsigned int current = pq.top().second;
		unsigned int cost = pq.top().first;
		pq.pop();

		for (unsigned int i = 0; i < graph[current].size(); i++) {
			unsigned int new_val = dist[current] + graph[current][i].val;
			unsigned int before_val = dist[graph[current][i].end];
 
			if (new_val < before_val) {
				dist[graph[current][i].end] = new_val;
				pq.push({new_val, graph[current][i].end});
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	unsigned int startnode = 0, vertex = 0, edge = 0;
	cin >> vertex>> edge >> startnode;
	startnode--;

	vector<vector<node>> graph = vector<vector<node>>(vertex);
	for (unsigned int i = 0, u, v, w; i < edge; i++) {
		cin >> u >> v >> w;
		u--, v--;
		graph[u].push_back(node{v, w});
	}

	vector<unsigned int> dist = vector<unsigned int>(vertex, INF);
	dist[startnode] = 0;
	dijkstra(graph, dist, startnode);

	for (unsigned int i = 0; i < dist.size(); i++) {
		if (dist[i] != INF) {
			cout << dist[i] << '\n';
		}
		else {
			cout << "INF\n";
		}
	}

	return 0;
}