#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pint;

const int MAX = 501;
const int INF = INT32_MAX / 2;

int testcase, n, m, w;
vector<vector<pint>> graph;
vector<int> dist;
bool has_neg_cycle;

void bellman_ford(int start) {
	dist[start] = 0;

	has_neg_cycle = false;
	for (int iter = 0; iter < n; iter++) {
		for (int i = 1; i <= n; ++i) {
			for (const pint& edge : graph[i]) {
				int nxt = edge.first;
				int edge_w = edge.second;

				if (dist[i] + edge_w < dist[nxt]) {
					dist[nxt] = dist[i] + edge_w;

					if (iter == n - 1) {
						has_neg_cycle = true;
					}
				}
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> testcase;
	do {
		cin >> n >> m >> w;

		graph = vector<vector<pint>>(n + 1);
		dist = vector<int>(n + 1, INF);
		for (int i = 0, arg1, arg2, weight; i < m; i++) {
			cin >> arg1 >> arg2 >> weight;
			graph[arg1].push_back(pint(arg2, weight));
			graph[arg2].push_back(pint(arg1, weight));
		}
		for (int i = 0, stt, end, weight; i < w; i++) {
			cin >> stt >> end >> weight;
			graph[stt].push_back(pint(end, -weight));
		}

		bellman_ford(1);
		cout << (has_neg_cycle ? "YES\n" : "NO\n");
	} while (--testcase > 0);

	return 0;
}