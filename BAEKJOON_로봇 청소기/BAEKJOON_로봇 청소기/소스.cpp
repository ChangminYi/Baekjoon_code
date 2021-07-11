#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

const int EMPTY = 0;
const int WALL = 1;
const int CLEANED = 2;
const vector<pint> dir = {
	{-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

pint robot;
int dir_idx;
int n, m;
int clean_count;
vector<vector<int>> board;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> n >> m >> robot.first >> robot.second >> dir_idx;
	board = vector<vector<int>>(n, vector<int>(m));
	for (vector<int>& row : board) {
		for (int& i : row) {
			cin >> i;
		}
	}

	clean_count = 1;
	board[robot.first][robot.second] = CLEANED;
	while (true) {
		int nxt_idx = (dir_idx + 3) % 4;
		pint nxt = make_pair(robot.first + dir[nxt_idx].first, robot.second + dir[nxt_idx].second);

		if (board[nxt.first][nxt.second] == EMPTY) {
			dir_idx = nxt_idx;
			robot = nxt;
			clean_count++;
			board[nxt.first][nxt.second] = CLEANED;
		}
		else {
			pint backward = make_pair(robot.first - dir[dir_idx].first, robot.second - dir[dir_idx].second);
			bool walled = true;
			for (const pint& p : dir) {
				pint tmp = make_pair(robot.first + p.first, robot.second + p.second);
				if (board[tmp.first][tmp.second] == EMPTY) {
					walled = false;
					break;
				}
			}

			if (walled) {
				if (board[backward.first][backward.second] == WALL) {
					break;
				}
				else {
					robot = backward;
				}
			}
			else {
				dir_idx = nxt_idx;
			}
		}
	}

	cout << clean_count;

	return 0;
}