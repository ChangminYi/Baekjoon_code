#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

const int INF = 1000000000;
int n = 0;
vector<vector<pint>> graph;

vector<int> dijk(int start) {
	vector<int> dist(n, INF);
	priority_queue<pint, vector<pint>, greater<pint>> pq;

	dist[start] = 0;
	pq.push(make_pair(dist[start], start));
	while (!pq.empty()) {
		int cur = pq.top().second;
		pq.pop();

		for (pint& p : graph[cur]) {
			int nxt = p.first;
			int new_val = dist[cur] + p.second;
			int old_val = dist[nxt];

			if (new_val < old_val) {
				dist[nxt] = new_val;
				pq.push(make_pair(new_val, nxt));
			}
		}
	}

	return dist;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	string tmp;
	deque<pair<pint, int>> edge;
	while (getline(cin, tmp)) {
		if (tmp.empty() || tmp == "0") {
			break;
		}
		else {
			stringstream s_in(tmp);
			int frt, bck, dst;
			s_in >> frt >> bck >> dst;

			n = max(frt, bck);
			edge.push_back(make_pair(make_pair(--frt, --bck), dst));
		}
	}

	if (n == 0) {
		cout << 0;
	}
	else {
		graph = vector<vector<pint>>(n);
		while (!edge.empty()) {
			int a = edge.front().first.first;
			int b = edge.front().first.second;
			int val = edge.front().second;
			edge.pop_front();

			graph[a].push_back(make_pair(b, val));
			graph[b].push_back(make_pair(a, val));
		}

		int max_val = 0;
		int max_idx = 0;
		vector<int> arg_dist = dijk(0);
		for (int i = 0; i < n; i++) {
			if (arg_dist[i] != INF && max_val < arg_dist[i]) {
				max_val = arg_dist[i];
				max_idx = i;
			}
		}

		max_val = 0;
		arg_dist = dijk(max_idx);
		for (int i = 0; i < n; i++) {
			if (arg_dist[i] != INF && max_val < arg_dist[i]) {
				max_val = arg_dist[i];
			}
		}

		cout << max_val;
	}

	return 0;
}