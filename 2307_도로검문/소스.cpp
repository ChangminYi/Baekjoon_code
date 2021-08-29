#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

const int NO_PARENT = 0;
const int INF = 1000000000;

vector<vector<pint>> graph;
vector<vector<bool>> usable;
vector<int> dist;
vector<int> parent;

void dijkstra(int start, bool update_parent) {
	fill(dist.begin(), dist.end(), INF);
	if (update_parent) {
		fill(parent.begin(), parent.end(), NO_PARENT);
	}
	priority_queue<pint, vector<pint>, greater<pint>> pq;
	
	dist[start] = 0;
	pq.push(make_pair(dist[start], start));
	while (!pq.empty()) {
		int cur = pq.top().second;
		int cur_dist = pq.top().first;
		pq.pop();

		if (cur_dist <= dist[cur]) {
			for (pint& nxt : graph[cur]) {
				int nxt_node = nxt.first;
				int new_val = dist[cur] + nxt.second;
				
				if (usable[cur][nxt_node] && new_val < dist[nxt_node]) {
					dist[nxt_node] = new_val;
					if (update_parent) {
						parent[nxt_node] = cur;
					}
					pq.push(make_pair(new_val, nxt_node));
				}
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	graph = vector<vector<pint>>(n + 1);
	usable = vector<vector<bool>>(n + 1, vector<bool>(n + 1));
	dist = vector<int>(n + 1);
	parent = vector<int>(n + 1);
	for (int i = 0; i < m; i++) {
		int arg1, arg2, val;
		cin >> arg1 >> arg2 >> val;
		graph[arg1].push_back(make_pair(arg2, val));
		graph[arg2].push_back(make_pair(arg1, val));
		usable[arg1][arg2] = true;
		usable[arg2][arg1] = true;
	}
	dijkstra(1, true);
	
	int min_dist = dist[n];
	int max_dist = 0;

	for (int cur = n, nxt; cur != 1; cur = parent[cur]) {
		nxt = parent[cur];

		usable[cur][nxt] = false;
		usable[nxt][cur] = false;

		dijkstra(1, false);
		if (dist[n] == INF) {
			max_dist = INF;
			break;
		}
		else {
			max_dist = max(max_dist, dist[n]);
		}

		usable[cur][nxt] = true;
		usable[nxt][cur] = true;
	}

	cout << (max_dist == INF ? -1 : max_dist - min_dist);

	return 0;
}