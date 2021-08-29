#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> pint;
typedef pair<int, pint> node;

const int EMPTY = 0;
const pint NO_FISH = { -1, -1 };
const vector<pint> dir = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

int b_size;
vector<vector<int>> board;
vector<vector<bool>> visit;
int shark_size = 2;
int eat_count = 0;
pint shark_pos;
int time_count = 0;

bool in_range(pint &p) {
	if (0 <= p.first && p.first < b_size) {
		if (0 <= p.second && p.second < b_size) {
			return true;
		}
	}
	return false;
}

bool can_eat(pint& p) {
	if (EMPTY < board[p.first][p.second] && board[p.first][p.second] < shark_size) {
		return true;
	}
	return false;
}

node dfs() {
	priority_queue<node, vector<node>, greater<node>> pq;
	queue<node> que;
	for (int i = 0; i < b_size; i++) {
		for (int j = 0; j < b_size; j++) {
			if (board[i][j] > shark_size) {
				visit[i][j] = true;
			}
			else {
				visit[i][j] = false;
			}
		}
	}

	que.push(make_pair(0, shark_pos));
	visit[shark_pos.first][shark_pos.second] = true;
	while (!que.empty()) {
		int cur_time = que.front().first;
		pint cur_pos = que.front().second;
		node cur = que.front();
		que.pop();

		if (can_eat(cur_pos)) {
			if (pq.empty() || cur_time == pq.top().first) {
				pq.push(cur);
			}
			else {
				break;
			}
		}
		else {
			for (const pint& p : dir) {
				pint nxt = make_pair(cur_pos.first + p.first, cur_pos.second + p.second);

				if (in_range(nxt) && !visit[nxt.first][nxt.second]) {
					visit[nxt.first][nxt.second] = true;
					que.push(make_pair(cur_time + 1, nxt));
				}
			}
		}
	}


	if (pq.empty()) {
		return make_pair(-1, make_pair(-1, -1));
	}
	else {
		return pq.top();
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> b_size;
	board = vector<vector<int>>(b_size, vector<int>(b_size));
	visit = vector<vector<bool>>(b_size, vector<bool>(b_size));
	for (int i = 0; i < b_size; i++) {
		for (int j = 0; j < b_size; j++) {
			cin >> board[i][j];

			if (board[i][j] == 9) {
				shark_pos.first = i;
				shark_pos.second = j;
				board[i][j] = EMPTY;
			}
		}
	}

	while (true) {
		node nxt = dfs();

		if (nxt.second == NO_FISH) {
			break;
		}
		else {
			board[nxt.second.first][nxt.second.second] = EMPTY;
			time_count += nxt.first;
			shark_pos = nxt.second;
			eat_count++;

			if (eat_count == shark_size) {
				shark_size++;
				eat_count = 0;
			}
		}
	}

	cout << time_count;

	return 0;
}