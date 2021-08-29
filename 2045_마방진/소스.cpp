#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int max_val = -1;
int board[3][3];
vector<pint> zero;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> board[i][j];

			if (board[i][j] == 0) {
				zero.push_back(make_pair(i, j));
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		max_val = max(max_val, board[i][0] + board[i][1] + board[i][2]);
		max_val = max(max_val, board[0][i] + board[1][i] + board[2][i]);
	}
	max_val = max(max_val, board[0][0] + board[1][1] + board[2][2]);
	max_val = max(max_val, board[0][2] + board[1][1] + board[2][0]);

	if (board[0][2] == 0 && board[1][1] == 0 && board[2][0] == 0) {
		board[2][0] = (board[0][1] + board[1][2]) / 2;
		board[0][2] = (board[1][0] + board[2][1]) / 2;
		board[1][1] = (board[2][0] + board[0][2]) / 2;
	}
	else if (board[0][0] == 0 && board[1][1] == 0 && board[2][2] == 0) {
		board[0][0] = (board[2][1] + board[1][2]) / 2;
		board[2][2] = (board[1][0] + board[0][1]) / 2;
		board[1][1] = (board[0][0] + board[2][2]) / 2;
	}
	else {
		for (pint& p : zero) {
			if (p.first == 0) {
				if (p.second == 0) {
					board[0][0] = max_val - max({ board[1][0] + board[2][0], board[1][1] + board[2][2], board[0][1] + board[0][2] });
				}
				else if (p.second == 1) {
					board[0][1] = max_val - max(board[0][0] + board[0][2], board[1][1] + board[2][1]);
				}
				else {
					board[0][2] = max_val - max({ board[0][0] + board[0][1], board[2][0] + board[1][1], board[1][2] + board[2][2] });
				}
			}
			else if (p.first == 1) {
				if (p.second == 0) {
					board[1][0] = max_val - max(board[0][0] + board[2][0], board[1][1] + board[1][2]);
				}
				else if (p.second == 1) {
					board[1][1] = max_val - max({ board[0][0] + board[2][2], board[2][0] + board[0][2], board[0][1] + board[2][1], board[1][0] + board[1][2] });
				}
				else {
					board[1][2] = max_val - max(board[1][0] + board[1][1], board[0][2] + board[2][2]);
				}
			}
			else {
				if (p.second == 0) {
					board[2][0] = max_val - max({ board[0][0] + board[1][0], board[1][1] + board[0][2], board[2][1] + board[2][2] });
				}
				else if (p.second == 1) {
					board[2][1] = max_val - max(board[2][0] + board[2][2], board[0][1] + board[1][1]);
				}
				else {
					board[2][2] = max_val - max({ board[2][0] + board[2][1], board[0][0] + board[1][1], board[0][2] + board[1][2] });
				}
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		cout << board[i][0] << ' ' << board[i][1] << ' ' << board[i][2] << '\n';
	}

	return 0;
}