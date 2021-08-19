#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef pair<int, int> pint;

int testcase, v, e;
vector<vector<int>> graph;
vector<pint> edge;
vector<bool> visit;
vector<bool> colored;

void dfs(int cur, int par) {
	colored[cur] = !colored[par];
	for (int& nxt : graph[cur]) {
		if (nxt != par && !visit[nxt]) {
			visit[nxt] = true;
			dfs(nxt, cur);
		}
	}
}

bool is_bipartite() {
	for (pint& p : edge) {
		if (colored[p.first] == colored[p.second]) {
			return false;
		}
	}

	return true;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> testcase;
	do {
		cin >> v >> e;
		graph = vector<vector<int>>(v + 1);
		edge = vector<pint>(e);
		visit = vector<bool>(v + 1, false);
		colored = vector<bool>(v + 1, false);
		for (pint& p : edge) {
			cin >> p.first >> p.second;
			graph[p.first].push_back(p.second);
			graph[p.second].push_back(p.first);
		}

		for (int i = 1; i <= v; i++) {
			if (!visit[i]) {
				visit[i] = true;
				dfs(i, 0);
			}
		}

		cout << (is_bipartite() ? "YES\n" : "NO\n");
	} while (--testcase > 0);

	return 0;
}