#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> dir = {
	{0, 1}, {0, -1}, { 1, 0}, {-1, 0},
	{1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};

int map[50][50] = { 0 };
bool visit[50][50] = { false };
int col = 0, row = 0;

bool inRange(const pair<int, int> &pos) {
	if (0 <= pos.first && pos.first < row) {
		if (0 <= pos.second && pos.second < col) {
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
	
	queue<pair<int, int>> togo;
	
	while (true) {
		int cnt = 0;
		cin >> col >> row;
		
		if (col == 0 && row == 0) {
			break;
		}
		else {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					cin >> map[i][j];
					visit[i][j] = false;
				}
			}

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {

					if (map[i][j] == 1 && !visit[i][j]) {
						cnt++;
						togo.push({ i, j });
						visit[i][j] = true;
						while (!togo.empty()) {
							pair<int, int> cur = togo.front();
							togo.pop();

							for (const pair<int, int>& t : dir) {
								pair<int, int> tmp = make_pair(t.first + cur.first, t.second + cur.second);
								
								if (inRange(tmp) && map[tmp.first][tmp.second] == 1 && !visit[tmp.first][tmp.second]) {
									visit[tmp.first][tmp.second] = true;
									togo.push(tmp);
								}
							}
						}
					}

				}
			}

			cout << cnt << '\n';
		}
	}

	return 0;
}