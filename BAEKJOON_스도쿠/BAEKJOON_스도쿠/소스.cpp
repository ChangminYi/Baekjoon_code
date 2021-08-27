#include <iostream>

using namespace std;

const int MAX = 9;

bool ans_find = false;
int board[MAX][MAX];
bool row[MAX][MAX] = { false };
bool col[MAX][MAX] = { false };
bool squ[MAX][MAX] = { false };

void dfs(int cnt) {
	if (!ans_find) {
		if (cnt == MAX * MAX) {
			ans_find = true;

			for (int i = 0; i < MAX; i++) {
				for (int j = 0; j < MAX; j++) {
					cout << board[i][j] << ' ';
				}
				cout << '\n';
			}
		}
		else {
			int x = cnt / MAX;
			int y = cnt % MAX;

			if (board[x][y] == 0) {
				for (int i = 1; i <= MAX; i++) {
					if (!row[x][i] && !col[y][i] && !squ[3 * (x / 3) + (y / 3)][i]) {
						row[x][i] = true;
						col[y][i] = true;
						squ[3 * (x / 3) + (y / 3)][i] = true;
						board[x][y] = i;

						dfs(cnt + 1);

						row[x][i] = false;
						col[y][i] = false;
						squ[3 * (x / 3) + (y / 3)][i] = false;
						board[x][y] = 0;
					}
				}
			}
			else {
				dfs(cnt + 1);
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			cin >> board[i][j];

			if (board[i][j] > 0) {
				row[i][board[i][j]] = true;
				col[j][board[i][j]] = true;
				squ[3 * (i / 3) + (j / 3)][board[i][j]] = true;
			}
		}
	}

	dfs(0);

	return 0;
}