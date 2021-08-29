#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
typedef pair<lli, int> node;

const lli INF = INT64_MAX / 2;

int v, e;
vector<vector<pint>> graph;
vector<vector<lli>> dist;
priority_queue<node, vector<node>, greater<node>> pq;

void init_dist(int start) {
	dist[start][start] = 0;
	pq.push(make_pair(dist[start][start], start));

	while (!pq.empty()) {
		lli cur_dist = pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		if (cur_dist <= dist[start][cur]) {
			for (pint& nxt : graph[cur]) {
				lli new_val = cur_dist + nxt.second;
				lli old_val = dist[start][nxt.first];

				if (new_val < old_val) {
					dist[start][nxt.first] = new_val;
					pq.push(make_pair(new_val, nxt.first));
				}
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> v >> e;
	graph = vector<vector<pint>>(v + 1);
	dist = vector<vector<lli>>(v + 1, vector<lli>(v + 1, INF));
	for (int i = 0; i < e; i++) {
		int arg1, arg2, val;
		cin >> arg1 >> arg2 >> val;
		graph[arg1].push_back(make_pair(arg2, val));
	}

	for (int i = 1; i <= v; i++) {
		init_dist(i);
	}

	lli min_dist = INF;
	for (int i = 1; i <= v; i++) {
		for (int j = i + 1; j <= v; j++) {
			if (dist[i][j] != INF && dist[j][i] != INF) {
				min_dist = min(min_dist, dist[i][j] + dist[j][i]);
			}
		}
	}

	cout << (min_dist == INF ? -1 : min_dist);

	return 0;
}