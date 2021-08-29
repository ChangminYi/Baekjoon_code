#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

const int INF = 1000000000;

int n, m;
vector<vector<pint>> graph;
vector<vector<int>> dist, prev_n;
priority_queue<pint, vector<pint>, greater<pint>> pq;
stack<int> route;

void dijkstra(int start) {
	prev_n[start][start] = start;
	dist[start][start] = 0;
	pq.push(make_pair(0, start));

	while(!pq.empty()){
		int cur = pq.top().second;
		int cur_dist = pq.top().first;
		pq.pop();

		if (cur_dist <= dist[start][cur]) {
			for (pint edge : graph[cur]) {
				int new_val = cur_dist + edge.second;
				int old_val = dist[start][edge.first];

				if (new_val < old_val) {
					dist[start][edge.first] = new_val;
					prev_n[start][edge.first] = cur;
					pq.push(make_pair(new_val, edge.first));
				}
			}
		}
	}
}

void floyd() {
	for (int i = 1; i <= n; i++) {
		dijkstra(i);
	}
}

void print_route(int start, int end) {
	if (start == end || dist[start][end] == INF) {
		cout << 0 << '\n';
	}
	else {
		route.push(end);
		while (prev_n[start][route.top()] != route.top()) {
			route.push(prev_n[start][route.top()]);
		}

		cout << route.size() << ' ';
		while (!route.empty()) {
			cout << route.top() << ' ';
			route.pop();
		}
		cout << '\n';
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	graph = vector<vector<pint>>(n + 1);
	dist = vector<vector<int>>(n + 1, vector<int>(n + 1, INF));
	prev_n = vector<vector<int>>(n + 1, vector<int>(n + 1));
	for (int i = 0, arg1, arg2, val; i < m; i++) {
		cin >> arg1 >> arg2 >> val;
		graph[arg1].push_back(make_pair(arg2, val));
	}

	floyd();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (dist[i][j] == INF) {
				cout << 0 << ' ';
			}
			else {
				cout << dist[i][j] << ' ';
			}
		}
		cout << '\n';
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			print_route(i, j);
		}
	}

	return 0;
}