#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;

const lli INF = INT64_MAX / 2;

int n, m;
bool negative_cycle = false;
vector<vector<pint>> graph;
vector<int> cycle;
vector<lli> dist;
vector<bool> in_queue;
queue<int> que;

void spfa(int start) {
	dist[start] = 0;
	in_queue[start] = true;
	que.push(start);

	while (!que.empty()) {
		int cur = que.front();
		in_queue[cur] = false;
		que.pop();

		for (pint& nxt : graph[cur]) {
			lli new_val = dist[cur] + nxt.second;
			lli old_val = dist[nxt.first];

			if (new_val < old_val) {
				dist[nxt.first] = new_val;

				if (!in_queue[nxt.first]) {
					cycle[nxt.first]++;

					if (cycle[nxt.first] < n) {
						que.push(nxt.first);
						in_queue[nxt.first] = true;
					}
					else {
						negative_cycle = true;
						return;
					}
				}
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	graph = vector<vector<pint>>(n + 1);
	cycle = vector<int>(n + 1, 0);
	dist = vector<lli>(n + 1, INF);
	in_queue = vector<bool>(n + 1, false);
	for (int i = 0; i < m; i++) {
		int arg1, arg2, val;
		cin >> arg1 >> arg2 >> val;
		graph[arg1].push_back(make_pair(arg2, val));
	}

	spfa(1);

	if (negative_cycle) {
		cout << -1;
	}
	else {
		for (int i = 2; i <= n; i++) {
			cout << (dist[i] == INF ? -1 : dist[i]) << '\n';
		}
	}

	return 0;
}