#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <functional>
#include <algorithm>
#include <limits>

using namespace std;

typedef pair<int, int> pint;

const int INF = INT32_MAX / 2;

int n, m, s, d;
vector<vector<int>> graph;
vector<vector<int>> weight;
vector<vector<int>> parent;

int dijkstra() {
	priority_queue<pint, vector<pint>, greater<pint>> pq;
	vector<int> dist(n, INF);

	dist[s] = 0;
	pq.push(make_pair(dist[s], s));
	while (!pq.empty()) {
		int cur = pq.top().second;
		int cur_dist = pq.top().first;
		pq.pop();

		if (cur_dist <= dist[cur]) {
			for (const int& nxt : graph[cur]) {
				int new_val = cur_dist + weight[cur][nxt];
				int old_val = dist[nxt];

				if (new_val == old_val) {
					parent[nxt].push_back(cur);
				}
				else if (new_val < old_val) {
					dist[nxt] = new_val;
					parent[nxt].clear();
					parent[nxt].push_back(cur);
					pq.push(make_pair(new_val, nxt));
				}
			}
		}
	}

	return dist[d];
}

void bfs() {
	queue<int> que;
	vector<bool> visit(n, false);
	
	visit[d] = true;
	que.push(d);
	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		for (const int& bef : parent[cur]) {
			graph[bef].erase(find(graph[bef].begin(), graph[bef].end(), cur));

			if (!visit[bef]) {
				visit[bef] = true;
				que.push(bef);
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	while (true) {
		cin >> n >> m;

		if (n == 0 && m == 0) {
			break;
		}
		else {
			graph = vector<vector<int>>(n);
			weight = vector<vector<int>>(n, vector<int>(n));
			parent = vector<vector<int>>(n);
			
			cin >> s >> d;
			for (int i = 0, u, v, p; i < m; i++) {
				cin >> u >> v >> p;
				graph[u].push_back(v);
				weight[u][v] = p;
			}

			dijkstra();
			bfs();

			int res = dijkstra();
			cout << (res == INF ? -1 : res) << '\n';
		}
	}

	return 0;
}