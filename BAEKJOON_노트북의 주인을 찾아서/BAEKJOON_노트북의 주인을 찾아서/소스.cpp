#include <iostream>
#include <vector>

using namespace std;

const int NOT_MATCH = -1;

int n, m;
vector<vector<int>> nb_set;
vector<int> req;
vector<bool> visit;

bool dfs(int cur) {
	for (int& nxt : nb_set[cur]) {
		if (!visit[nxt]) {
			visit[nxt] = true;

			if (req[nxt] == NOT_MATCH || dfs(req[nxt])) {
				req[nxt] = cur;
				return true;
			}
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	nb_set = vector<vector<int>>(n + 1);
	req = vector<int>(n + 1, NOT_MATCH);
	visit = vector<bool>(n + 1);
	for (int i = 0, arg1, arg2; i < m; i++) {
		cin >> arg1 >> arg2;
		nb_set[arg1].push_back(arg2);
	}

	int max_match = 0;
	for (int i = 1; i <= n; i++) {
		fill(visit.begin(), visit.end(), false);
		if (dfs(i)) {
			max_match++;
		}
	}

	cout << max_match;

	return 0;
}