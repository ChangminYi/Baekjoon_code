#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> pint;
typedef pair<pint, pint> pq_node;
const vector<pint> poss_dir = {
	pint(1, 0),
	pint(-1, 0),
	pint(0, 1),
	pint(0, -1)
};

const int NOT_VISIT = -1;

int n, m;
bool ans_find = false;
vector<vector<char>> board;
vector<vector<bool>> visit;
vector<pint> trash;
pint st;
priority_queue<pq_node, vector<pq_node>, greater<pq_node>> pq;

pint operator+(const pint& lhs, const pint& rhs) {
	return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
	return (0 <= p.first && p.first < n) && (0 <= p.second && p.second < m);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	board.resize(n, vector<char>(m));
	visit.resize(n, vector<bool>(m, false));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; ++j) {
			cin >> board[i][j];

			if (board[i][j] == 'S') {
				st = pint(i, j);
			}
			else if (board[i][j] == 'g') {
				trash.push_back(pint(i, j));
			}
		}
	}
	for (const pint& cur : trash) {
		for (const pint& dir : poss_dir) {
			pint nxt = cur + dir;

			if (in_range(nxt) && board[nxt.first][nxt.second] == '.') {
				board[nxt.first][nxt.second] = 'a';
			}
		}
	}

	pq.push(pq_node(pint(0, 0), st));
	visit[st.first][st.second] = true;
	while (!pq.empty() && !ans_find) {
		int gar_cnt = pq.top().first.first;
		int adj_cnt = pq.top().first.second;
		pint cur = pq.top().second;
		pq.pop();

		for (int i = 0; i < poss_dir.size() && !ans_find; i++) {
			pint nxt = cur + poss_dir[i];

			if (in_range(nxt) && !visit[nxt.first][nxt.second]) {
				if (board[nxt.first][nxt.second] == 'F') {
					cout << gar_cnt << ' ' << adj_cnt;
					ans_find = true;
				}
				else {
					visit[nxt.first][nxt.second] = true;

					if (board[nxt.first][nxt.second] == '.') {
						pq.push(pq_node(pint(gar_cnt, adj_cnt), nxt));
					}
					else if (board[nxt.first][nxt.second] == 'a') {
						pq.push(pq_node(pint(gar_cnt, adj_cnt + 1), nxt));
					}
					else {
						pq.push(pq_node(pint(gar_cnt + 1, adj_cnt), nxt));
					}
				}
			}
		}
	}

	return 0;
}