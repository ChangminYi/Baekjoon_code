#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

const int INF = 1000000000;
const int NO_PARENT = 0;
int n, m, t;
vector<vector<pint>> graph;
vector<int> candidate;
priority_queue<pint, vector<pint>, greater<pint>> pq;

vector<int> dijkstra(int start) {
	vector<int> dist(n + 1, INF);
	dist[start] = 0;
	pq.push(make_pair(dist[start], start));

	while (!pq.empty()) {
		int cur = pq.top().second;
		int cur_dist = pq.top().first;
		pq.pop();

		if (cur_dist <= dist[cur]) {
			for (pint& nxt : graph[cur]) {
				int new_val = dist[cur] + nxt.second;
				int old_val = dist[nxt.first];

				if (new_val < old_val) {
					dist[nxt.first] = new_val;
					pq.push(make_pair(new_val, nxt.first));
				}
			}
		}
	}

	return dist;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int test_case;
	cin >> test_case;
	do {
		pint m_path;
		int start, inter_dist = 0;

		cin >> n >> m >> t >> start >> m_path.first >> m_path.second;
		graph = vector<vector<pint>>(n + 1);
		candidate = vector<int>(t);
		for (int i = 0, arg1, arg2, val; i < m; i++) {
			cin >> arg1 >> arg2 >> val;
			graph[arg1].push_back(make_pair(arg2, val));
			graph[arg2].push_back(make_pair(arg1, val));

			if ((arg1 == m_path.first && arg2 == m_path.second) || (arg1 == m_path.second && arg2 == m_path.first)) {
				inter_dist = val;
			}
		}
		for (int& i : candidate) {
			cin >> i;
		}
		sort(candidate.begin(), candidate.end());

		vector<int> stt = dijkstra(start);
		vector<int> from_first = dijkstra(m_path.first);
		vector<int> from_second = dijkstra(m_path.second);

		for (int& cnd : candidate) {
			int f_dist = stt[m_path.first] + inter_dist + from_second[cnd];
			int s_dist = stt[m_path.second] + inter_dist + from_first[cnd];

			if (stt[cnd] == f_dist || stt[cnd] == s_dist) {
				cout << cnd << ' ';
			}
		}
		cout << '\n';

	} while (--test_case > 0);

	return 0;
}