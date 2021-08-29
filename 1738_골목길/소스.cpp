#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef long long lli;
typedef pair<int, lli> pint;

const lli INF = INT64_MAX / 2;
const lli NO_PARENT = 0;

int n, m;
bool has_cycle = false;
vector<vector<pint>> graph;
vector<vector<int>> rev_graph;
vector<bool> rev_reach;
vector<lli> dist;
vector<int> parent;
vector<int> cycle;
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

		for (pint& edge : graph[cur]) {
			int nxt = edge.first;
			lli edge_w = edge.second;

			lli new_val = dist[cur] + edge_w;
			lli old_val = dist[nxt];

			if (new_val < old_val) {
				dist[nxt] = new_val;
				parent[nxt] = cur;

				if (!in_queue[nxt]) {
					cycle[nxt]++;

					if (cycle[nxt] < n) {
						que.push(nxt);
						in_queue[nxt] = true;
					}
					else if (cycle[nxt] == n && rev_reach[cur]) {
						has_cycle = true;
						return;
					}
				}
			}
		}
	}
}

void update_visit(int start) {
	rev_reach[start] = true;
	que.push(start);

	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		for (int& nxt : rev_graph[cur]) {
			if (!rev_reach[nxt]) {
				rev_reach[nxt] = true;
				que.push(nxt);
			}
		}
	}
}

void print_route(int cur) {
	if (cur != 1) {
		print_route(parent[cur]);
	}
	cout << cur << ' ';
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	graph = vector<vector<pint>>(n + 1);
	rev_graph = vector<vector<int>>(n + 1);
	rev_reach = vector<bool>(n + 1, false);
	dist = vector<lli>(n + 1, INF);
	parent = vector<int>(n + 1, NO_PARENT);
	cycle = vector<int>(n + 1, 0);
	in_queue = vector<bool>(n + 1, false);
	for (int i = 0; i < m; i++) {
		int arg1, arg2;
		lli val;
		cin >> arg1 >> arg2 >> val;
		graph[arg1].push_back(make_pair(arg2, val * (-1)));
		rev_graph[arg2].push_back(arg1);
	}

	update_visit(n);
	spfa(1);

	if (has_cycle) {
		cout << -1;
	}
	else {
		print_route(n);
	}

	return 0;
}