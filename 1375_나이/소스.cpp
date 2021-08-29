#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <numeric>

using namespace std;

const int NOT_VISIT = 0;
const int LO_VISIT = 1;
const int HI_VISIT = 2;

int n, m, q;
vector<int> degree, level;
vector<vector<int>> graph, rev_graph;
unordered_map<string, int> idx;
vector<int> visit;
queue<int> que;

bool in_map(const string& str) {
	return idx.find(str) != idx.end();
}

bool find_lca(int lo, int hi) {
	fill(visit.begin(), visit.end(), NOT_VISIT);
	vector<int> lcas;
	
	visit[lo] = LO_VISIT;
	que.push(lo);
	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		for (const int& nxt : rev_graph[cur]) {
			if (visit[nxt] == NOT_VISIT) {
				visit[nxt] = LO_VISIT;
				que.push(nxt);
			}
		}
	}

	visit[hi] = HI_VISIT;
	que.push(hi);
	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		for (const int& nxt : rev_graph[cur]) {
			if (visit[nxt] == LO_VISIT) {
				lcas.push_back(nxt);
			}
			else if(visit[nxt] == NOT_VISIT && level[nxt] >= level[lo]) {
				visit[nxt] = HI_VISIT;
				que.push(nxt);
			}
		}
	}

	return find(lcas.begin(), lcas.end(), lo) != lcas.end();
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	(cin >> n >> m).ignore();

	degree.resize(n, 0);
	level.resize(n, 0);
	graph.resize(n);
	rev_graph.resize(n);
	visit.resize(n);

	for (int i = 0, idx_cnt = 0; i < m; i++) {
		string str1, str2;
		cin >> str1 >> str2;

		if (!in_map(str1)) {
			idx.insert(make_pair(str1, idx_cnt++));
		}
		if (!in_map(str2)) {
			idx.insert(make_pair(str2, idx_cnt++));
		}

		degree[idx[str1]]++;
		graph[idx[str2]].push_back(idx[str1]);
		rev_graph[idx[str1]].push_back(idx[str2]);
	}

	for (auto i = idx.begin(); i != idx.end(); i++) {
		if (degree[i->second] == 0) {
			que.push(i->second);
		}
	}
	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		for (const int& nxt : graph[cur]) {
			degree[nxt]--;
			level[nxt] = max(level[nxt], level[cur] + 1);

			if (degree[nxt] == 0) {
				que.push(nxt);
			}
		}
	}

	(cin >> q).ignore();
	do {
		string str1, str2;
		cin >> str1 >> str2;

		if (!in_map(str1) || !in_map(str2)) {
			cout << "gg ";
		}
		else {
			int idx1 = idx[str1], idx2 = idx[str2];

			if (level[idx1] == level[idx2]) {
				cout << "gg ";
			}
			else {
				int hi = (level[idx1] > level[idx2] ? idx1 : idx2);
				int lo = (hi == idx1 ? idx2 : idx1);

				if (find_lca(lo, hi)) {
					cout << (level[idx1] > level[idx2] ? str1 : str2) << ' ';
				}
				else {
					cout << "gg ";
				}
			}
		}
	} while (--q > 0);

	return 0;
}