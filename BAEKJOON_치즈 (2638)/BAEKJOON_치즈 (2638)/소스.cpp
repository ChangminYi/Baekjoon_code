#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

vector<pint> dir = {
	{0, 1}, {0, -1}, {1, 0}, {-1, 0}
};
const int CHEESE = 1;
const int EMPTY = 0;

int n, m, time_count = 0;
vector<vector<bool>> visit;
vector<vector<bool>> outer;
vector<vector<int>> board;
queue<pint> que;

const pint operator+(const pint& a, const pint& b) {
	return make_pair(a.first + b.first, a.second + b.second);
}

bool in_range(pint& p) {
	return (0 <= p.first && p.first < n && 0 <= p.second && p.second < m);
}

void update_board() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visit[i][j] = false;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == EMPTY && outer[i][j] && !visit[i][j]) {
				que.push(make_pair(i, j));
				visit[i][j] = true;

				while (!que.empty()) {
					pint cur = que.front();
					que.pop();

					for (pint& p : dir) {
						pint nxt = cur + p;

						if (in_range(nxt) && board[nxt.first][nxt.second] == EMPTY && !visit[nxt.first][nxt.second]) {
							visit[nxt.first][nxt.second] = true;
							outer[nxt.first][nxt.second] = true;
							que.push(nxt);
						}
					}
				}
			}
		}
	}
}

void get_cheese() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == CHEESE) {
				int adj_cnt = 0;
				pint cur = make_pair(i, j);
				for (pint& p : dir) {
					pint nxt = cur + p;
					if (board[nxt.first][nxt.second] == EMPTY && outer[nxt.first][nxt.second]) {
						adj_cnt++;
					}
				}
				if (adj_cnt >= 2) {
					que.push(cur);
				}
			}
		}
	}
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	board = vector<vector<int>>(n, vector<int>(m));
	outer = vector<vector<bool>>(n, vector<bool>(m, false));
	visit = vector<vector<bool>>(n, vector<bool>(m, false));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}

	outer[0][0] = true;
	while (true) {
		update_board();
		get_cheese();

		if (que.empty()) {
			break;
		}
		else {
			time_count++;
			while (!que.empty()) {
				board[que.front().first][que.front().second] = EMPTY;
				outer[que.front().first][que.front().second] = true;
				que.pop();
			}
		}
	}

	cout << time_count;

	return 0;
}