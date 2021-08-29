#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;
typedef pair<pint, int> dat;

const int EMPTY = 0;
const vector<pint> dir = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

bool in_range(const int& x, const int& y, const vector<vector<int>>& board) {
	if (0 <= x && x < board.size()) {
		if (0 <= y && y < board.front().size()) {
			return true;
		}
	}
	return false;
}

queue<dat> get_reduce(vector<vector<int>>& board) {
	queue<dat> que;

	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board.front().size(); j++) {
			if (board[i][j] != EMPTY) {
				int tmp_cnt = 0;
				for (const pint& p : dir) {
					int nxt_x = i + p.first;
					int nxt_y = j + p.second;

					if (in_range(nxt_x, nxt_y, board) && board[nxt_x][nxt_y] == EMPTY) {
						tmp_cnt++;
					}
				}

				que.push(make_pair(make_pair(i, j), tmp_cnt));
			}
		}
	}

	return que;
}

int get_sub(vector<vector<int>>& board) {
	vector<vector<bool>> visit(board.size(), vector<bool>(board.front().size(), false));
	int sub_count = 0;

	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board.front().size(); j++) {
			if (board[i][j] != EMPTY && !visit[i][j]) {
				sub_count++;
				queue<pint> que;
				que.push(make_pair(i, j));
				visit[i][j] = true;
				while (!que.empty()) {
					pint cur = que.front();
					que.pop();
					for (const pint& p : dir) {
						pint nxt = make_pair(cur.first + p.first, cur.second + p.second);

						if (in_range(nxt.first, nxt.second, board)) { 
							if (board[nxt.first][nxt.second] != EMPTY && !visit[nxt.first][nxt.second]) {
								visit[nxt.first][nxt.second] = true;
								que.push(nxt);
							}
						}
					}
				}
			}
		}
	}

	return sub_count;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m, time_count = 0;
	cin >> n >> m;
	vector<vector<int>> board(n, vector<int>(m));
	for (vector<int>& row : board) {
		for (int& i : row) {
			cin >> i;
		}
	}

	while (true) {
		time_count++;
		queue<dat> to_rdc= get_reduce(board);

		if (to_rdc.empty()) {
			time_count = 0;
			break;
		}
		else {
			while (!to_rdc.empty()) {
				pint cur = to_rdc.front().first;
				int rdc_val = to_rdc.front().second;
				to_rdc.pop();
				board[cur.first][cur.second] = max(board[cur.first][cur.second] - rdc_val, EMPTY);
			}

			if (get_sub(board) >= 2) {
				break;
			}
		}
	}

	cout << time_count;

	return 0;
}