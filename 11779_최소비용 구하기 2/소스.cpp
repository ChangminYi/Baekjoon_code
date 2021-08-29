#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

const int INF = 1000000000;
const int MAX_NODE = 1001;

vector<vector<pint>> graph(MAX_NODE);
vector<int> dist(MAX_NODE, INF);
vector<int> parent(MAX_NODE);
priority_queue<pint, vector<pint>, greater<pint>> pq;
stack<int> trace;

void dijk(int start, int destination) {
	dist[start] = 0;
	pq.push(make_pair(dist[start], start));

	while (!pq.empty()) {
		int cur = pq.top().second;
		int cur_val = pq.top().first;
		pq.pop();

		if (dist[cur] >= cur_val) {
			for (pint& edge : graph[cur]) {
				int nxt = edge.first;
				int new_val = cur_val + edge.second;

				if (new_val < dist[nxt]) {
					parent[nxt] = cur;
					dist[nxt] = new_val;
					pq.push(make_pair(new_val, nxt));
				}
			}
		}
	}

	trace.push(destination);
	while (trace.top() != start) {
		trace.push(parent[trace.top()]);
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m, depart, arrival;
	cin >> n >> m;
	for (int i = 0, stt, dst, val; i < m; i++) {
		cin >> stt >> dst >> val;
		graph[stt].push_back(make_pair(dst, val));
	}

	cin >> depart >> arrival;
	dijk(depart, arrival);

	cout << dist[arrival] << '\n' << trace.size() << '\n';
	while (!trace.empty()) {
		cout << trace.top() << ' ';
		trace.pop();
	}

	return 0;
}