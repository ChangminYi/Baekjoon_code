#include <iostream>
#include <vector>
#include <deque>

using namespace std;

typedef pair<int, char> dat;
typedef pair<int, int> pint;

const int EMPTY = 0;
const int APPLE = 1;

int n, k;
const vector<pint> direc = {
	{0, 1}, {1, 0}, {0, -1}, {-1, 0}
};
int dir_idx = 0;
vector<vector<int>> board;
deque<dat> inst;
deque<pint> snake;

void turn_right() {
	dir_idx = (dir_idx + 5) % 4;
}

void turn_left() {
	dir_idx = (dir_idx + 3) % 4;
}

bool in_board() {
	if (0 <= snake.front().first && snake.front().first < n) {
		if (0 <= snake.front().second && snake.front().second < n) {
			return true;
		}
	}
	return false;
}

bool touch_body() {
	for (size_t i = 1; i < snake.size(); i++) {
		if (snake.front() == snake[i]) {
			return true;
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> n >> k;
	board = vector<vector<int>>(n, vector<int>(n, EMPTY));
	for (int i = 0, row, col; i < k; i++) {
		cin >> row >> col;
		board[--row][--col] = APPLE;
	}

	int n_inst;
	cin >> n_inst;
	inst = deque<dat>(n_inst);
	for (dat& d : inst) {
		cin >> d.first >> d.second;
	}

	snake.push_back(make_pair(0, 0));
	for (int time_cnt = 0; ; ) {
		time_cnt++;

		pint new_head = make_pair(snake.front().first + direc[dir_idx].first, snake.front().second + direc[dir_idx].second);
		snake.push_front(new_head);
		if (in_board() && !touch_body()) {
			if (board[new_head.first][new_head.second] == APPLE) {
				board[new_head.first][new_head.second] = EMPTY;
			}
			else {
				snake.pop_back();
			}
		}
		else {
			cout << time_cnt;
			break;
		}

		if (!inst.empty() && inst.front().first == time_cnt) {
			if (inst.front().second == 'L') {
				turn_left();
			}
			else if(inst.front().second == 'D') {
				turn_right();
			}
			inst.pop_front();
		}
	}

	return 0;
}