#include <iostream>
#include <vector>

using namespace std;

int n, L;
vector<vector<int>> board, trans;
vector<vector<bool>> slope, t_slope;

bool in_range(const int& row, const int& col) {
	if (0 <= row && row < n && 0 <= col && col < n) {
		return true;
	}
	return false;
}

bool all_same(const int& row, const int& col, vector<vector<int>> &bo) {
	for (int i = col + 1; i < col + L; i++) {
		if (bo[row][i] != bo[row][i + 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> n >> L;
	board = vector<vector<int>>(n, vector<int>(n));
	trans = vector<vector<int>>(n, vector<int>(n));
	slope = vector<vector<bool>>(n, vector<bool>(n, false));
	t_slope = vector<vector<bool>>(n, vector<bool>(n, false));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
			trans[j][i] = board[i][j];
		}
	}

	int total_count = 2 * n;
	for (int i = 0, idx; i < n; i++) {
		idx = 0;
		while (idx < n) {
			if (in_range(i, idx + 1) && board[i][idx] == board[i][idx + 1]) {
				idx++;
			}
			else if (in_range(i, idx + L) && board[i][idx] - 1 == board[i][idx + 1] && all_same(i, idx, board)) {
				for (int j = idx + 1; j <= idx + L; j++) {
					slope[i][j] = true;
				}
				idx += L;
			}
			else if (in_range(i, idx - L + 1) && board[i][idx] + 1 == board[i][idx + 1] && all_same(i, idx - L, board)) {
				for (int j = idx - L + 1; j <= idx; j++) {
					if (slope[i][j]) {
						idx = -1;
						break;
					}
				}

				if (idx == -1) {
					idx = 0;
					total_count--;
					break;
				}
				else {
					idx += 1;
				}
			}
			else {
				idx = 0;
				total_count--;
				break;
			}

			if (idx == n - 1) {
				idx = 0;
				break;
			}
		}
	}
	for (int i = 0, idx; i < n; i++) {
		idx = 0;
		while (idx < n) {
			if (in_range(i, idx + 1) && trans[i][idx] == trans[i][idx + 1]) {
				idx++;
			}
			else if (in_range(i, idx + L) && trans[i][idx] - 1 == trans[i][idx + 1] && all_same(i, idx, trans)) {
				for (int j = idx + 1; j <= idx + L; j++) {
					t_slope[i][j] = true;
				}
				idx += L;
			}
			else if (in_range(i, idx - L + 1) && trans[i][idx] + 1 == trans[i][idx + 1] && all_same(i, idx - L, trans)) {
				for (int j = idx - L + 1; j <= idx; j++) {
					if (t_slope[i][j]) {
						idx = -1;
						break;
					}
				}

				if (idx == -1) {
					idx = 0;
					total_count--;
					break;
				}
				else {
					idx += 1;
				}
			}
			else {
				idx = 0;
				total_count--;
				break;
			}

			if (idx == n - 1) {
				break;
			}
		}
	}

	cout << total_count;

	return 0;
}