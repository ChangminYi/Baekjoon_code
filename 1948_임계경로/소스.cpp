#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class edge {
public:
	int adj_node = 0;
	int weight = 0;
	edge(int _adj, int _w) : adj_node(_adj), weight(_w) {}
};

int n, m;
int starting, meeting;
vector<vector<edge>> graph, rev_graph;
vector<int> degree, max_time;
vector<bool> visit;
queue<int> que;

void get_max_time() {
	que.push(starting);
	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		for (const edge& e : graph[cur]) {
			int nxt = e.adj_node;

			degree[nxt]--;
			max_time[nxt] = max(max_time[nxt], max_time[cur] + e.weight);
			if (degree[nxt] == 0) {
				que.push(nxt);
			}
		}
	}
}

int get_longest_path() {
	int road_count = 0;

	que.push(meeting);
	visit[meeting] = true;

	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		for (const edge& e : rev_graph[cur]) {
			int prev = e.adj_node;

			if (max_time[prev] + e.weight == max_time[cur]) {
				road_count++;

				if (!visit[prev]) {
					visit[prev] = true;
					que.push(prev);
				}
			}
		}
	}

	return road_count;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	graph = vector<vector<edge>>(n + 1);
	rev_graph = vector<vector<edge>>(n + 1);
	degree = vector<int>(n + 1, 0);
	max_time = vector<int>(n + 1, 0);
	visit = vector<bool>(n + 1, false);
	for (int i = 0, arg1, arg2, arg3; i < m; i++) {
		cin >> arg1 >> arg2 >> arg3;
		graph[arg1].push_back(edge(arg2, arg3));
		rev_graph[arg2].push_back(edge(arg1, arg3));
		degree[arg2]++;
	}
	cin >> starting >> meeting;

	get_max_time();
	cout << max_time[meeting] << '\n' << get_longest_path();

	return 0;
}