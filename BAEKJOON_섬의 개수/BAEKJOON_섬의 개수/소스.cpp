#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX 50

const vector<pair<int, int>> move = {
	{0, 1}, {0, -1}, { 1, 0}, {-1, 0},
	{1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};
queue<pair<int, int>> togo;
vector<vector<bool>> visit(MAX, vector<bool>(MAX));
vector<vector<int>> map(MAX, vector<int>(MAX));
int r = 0, c = 0, island = 0, i = 0, j = 0;
uint32_t k = 0;
pair<int, int> range, cur, temp;

bool inRange(const pair<int, int> &a, const pair<int, int> &range) {
	if (0 <= a.first && a.first < range.first) {
		if (0 <= a.second && a.second < range.second) {
			return true;
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);

	while (true) {
		cin >> c >> r;
		if (r == 0 && c == 0) {
			break;
		}
		else {
			for (i = 0; i < r; i++) {
				for (j = 0; j < c; j++) {
					cin >> map[i][j];
					visit[i][j] = false;
				}
			}

			island = 0;
			range.first = r;
			range.second = c;
			for (i = 0; i < r; i++) {
				for (j = 0; j < c; j++) {
					if (map[i][j] == 1 && !visit[i][j]) {
						island++;

						togo.push(make_pair(i, j));
						while (!togo.empty()) {
							cur.first = togo.front().first;
							cur.second = togo.front().second;
							visit[cur.first][cur.second] = true;
							togo.pop();

							for (k = 0; k < ::move.size(); k++) {
								temp.first = cur.first + ::move[k].first;
								temp.second = cur.second + ::move[k].second;
								if (inRange(temp, range) && map[temp.first][temp.second] == 1 && !visit[temp.first][temp.second]) {
									togo.push(temp);
								}
							}
						}
					}
				}
			}

			cout << island << '\n';
		}
	}

	return 0;
}