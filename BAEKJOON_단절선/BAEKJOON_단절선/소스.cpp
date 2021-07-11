#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

const int NOT_VISIT = 0;
vector<vector<int>> graph;
vector<pint> cut_edge;
vector<int> discov;
int visit_cnt = 0;

int dfs(int cur, int parent) {
	discov[cur] = ++visit_cnt;
	int ret = discov[cur];

	for (int& nxt : graph[cur]) {
		if (nxt == parent) {
			continue;
		}
		else {
			if (discov[nxt] == NOT_VISIT) {
				int lo_val = dfs(nxt, cur);

				if (lo_val > discov[cur]) {
					cut_edge.push_back(make_pair(min(cur, nxt), max(cur, nxt)));
				}
				ret = min(ret, lo_val);
			}
			else {
				ret = min(ret, discov[nxt]);
			}
		}
	}

	return ret;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int v, e;
	cin >> v >> e;
	graph = vector<vector<int>>(v + 1);
	discov = vector<int>(v + 1, NOT_VISIT);
	for (int i = 0, arg1, arg2; i < e; i++) {
		cin >> arg1 >> arg2;
		graph[arg1].push_back(arg2);
		graph[arg2].push_back(arg1);
	}

	dfs(1, 0);

	sort(cut_edge.begin(), cut_edge.end());
	cout << cut_edge.size() << '\n';
	for (pint& p : cut_edge) {
		cout << p.first << ' ' << p.second << '\n';
	}

	return 0;
}