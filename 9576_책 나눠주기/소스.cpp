#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

const int NOT_MATCH = -1;

int n, m, match_count, testcase;
vector<pint> book_req;
vector<int> book_match;
vector<bool> visit;

bool dfs(int cur) {
	for (int nxt = book_req[cur].first; nxt <= book_req[cur].second; nxt++) {
		if (!visit[nxt]) {
			visit[nxt] = true;

			if (book_match[nxt] == NOT_MATCH || dfs(book_match[nxt])) {
				book_match[nxt] = cur;
				return true;
			}
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> testcase;
	do {
		cin >> n >> m;
		book_req = vector<pint>(m);
		book_match = vector<int>(n + 1, NOT_MATCH);
		visit = vector<bool>(n + 1);

		for (int i = 0; i < m; i++) {
			cin >> book_req[i].first >> book_req[i].second;
		}

		match_count = 0;
		for (int i = 0; i < m; i++) {
			fill(visit.begin(), visit.end(), false);
			if (dfs(i)) {
				match_count++;
			}
		}
		cout << match_count << '\n';
	} while (--testcase > 0);

	return 0;
}