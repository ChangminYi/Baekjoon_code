#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef class NODE {
public:
	pair<int, int> dir;
	int date;

	NODE() {};
	NODE(pair<int, int> p, int d) : dir(p), date(d) {};
}node;


vector<pair<int, int>> move = {
	{0, 1},
	{0, -1}, 
	{1, 0}, 
	{-1, 0}
};

bool isInRange(pair<int, int> &dir, vector<vector<int>> &board) {
	if (0 <= dir.first && dir.first < board.size() && 0 <= dir.second && dir.second < board.front().size()) {
		return true;
	}
	return false;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	uint32_t row = 0, col = 0;
	cin >> col >> row;

	queue<node> q;
	int num_zero = 0;
	vector<vector<int>> board = vector<vector<int>>(row, vector<int>(col));
	for (uint32_t i = 0; i < row; i++) {
		for (uint32_t j = 0; j < col; j++) {
			cin >> board[i][j];

			if (board[i][j] == 0) {
				num_zero++;
			}
			else if (board[i][j] == 1) {
				q.push(node(make_pair(i, j), 0));
			}
		}
	}

	int day_count = -1;
	vector<vector<bool>> check = vector<vector<bool>>(row, vector<bool>(col, false));
	while (!q.empty()) {
		node cur = q.front();
		q.pop();
		day_count = max(day_count, cur.date);

		for (pair<int, int> &m : ::move) {
			pair<int, int> nxt = { cur.dir.first + m.first, cur.dir.second + m.second };

			if (isInRange(nxt, board) && board[nxt.first][nxt.second] == 0 && !check[nxt.first][nxt.second]) {
				q.push(node(nxt, cur.date + 1));
				board[nxt.first][nxt.second] = 1;
				check[nxt.first][nxt.second] = true;
				num_zero--;
			}
		}
	}

	cout << (num_zero == 0 ? day_count : -1);

	return 0;
}