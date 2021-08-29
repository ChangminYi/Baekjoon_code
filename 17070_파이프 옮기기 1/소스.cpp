#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;
typedef class PIPE {
public:
	pint head, tail;
	PIPE() {}
	PIPE(pint _head, pint _tail) : head(_head), tail(_tail) {}
}pipe;

vector<pint> dir = {
	{0, 1}, {1, 1}, {1, 0}
};

bool in_range(pint& p, vector<vector<bool>> &board) {
	if (0 <= p.first && p.first < board.size()) {
		if (0 <= p.second && p.second < board.size()) {
			return true;
		}
	}
	return false;
}

bool is_diagonal(pipe &p) {
	if (p.head.first - p.tail.first == 1) {
		if (p.head.second - p.tail.second == 1) {
			return true;
		}
	}
	return false;
}

bool is_horizontal(pipe& p) {
	if (p.head.first == p.tail.first) {
		return true;
	}
	return false;
}

bool is_vertical(pipe& p) {
	if (p.head.second == p.tail.second) {
		return true;
	}
	return false;
}

bool is_orthogonal(pipe &front, pipe& last) {
	if (is_diagonal(front)) {
		return false;
	}
	else {
		if (is_horizontal(front) && is_vertical(last)) {
			return true;
		}
		if (is_vertical(front) && is_horizontal(last)) {
			return true;
		}
	}
	return false;
}

bool is_empty_board(pipe& p, vector<vector<bool>>& board) {
	if (is_diagonal(p)) {
		for (pint& to_srch : dir) {
			pint tmp = make_pair(p.tail.first + to_srch.first, p.tail.second + to_srch.second);

			if (!board[tmp.first][tmp.second]) {
				return false;
			}
		}
		return true;
	}
	else {
		if (board[p.head.first][p.head.second]) {
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

	int n;
	cin >> n;

	vector<vector<bool>> can_move(n, vector<bool>(n, false));
	vector<vector<int>> move_cnt(n, vector<int>(n, 0));
	for (int i = 0, tmp; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> tmp;
			if (tmp == 0) {
				can_move[i][j] = true;
			}
			else {
				can_move[i][j] = false;
			}
		}
	}

	queue<pipe> que;
	que.push(pipe(make_pair(0, 1), make_pair(0, 0)));
	while (!que.empty()) {
		pipe cur = que.front();
		que.pop();
		move_cnt[cur.head.first][cur.head.second]++;

		for (pint& to_add : dir) {
			pint nxt_tmp = make_pair(cur.head.first + to_add.first, cur.head.second + to_add.second);
			pipe nxt = pipe(nxt_tmp, cur.head);

			if (in_range(nxt_tmp, can_move) && is_empty_board(nxt, can_move)) {
				if (!is_orthogonal(nxt, cur)) {
					que.push(nxt);
				}
			}
		}
	}

	cout << move_cnt.back().back();

	return 0;
}