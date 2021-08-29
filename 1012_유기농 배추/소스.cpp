#include <iostream>
#include <deque>
#include <vector>

using namespace std;

bool isInRange(int row, int col, vector<vector<bool>> &arg) {
	if ((0 <= row && row < arg.size()) && (0 <= col && col < arg.front().size())) {
		return true;
	}
	else {
		return false;
	}
}

int getNumber(vector<vector<bool>> &arg) {
	int num = 0;
	vector<vector<bool>> check(arg.size(), vector<bool>(arg.front().size(), false));

	for (uint32_t i = 0; i < arg.size(); i++) {
		for (uint32_t j = 0; j < arg.front().size(); j++) {
			if (arg[i][j] && !check[i][j]) {
				num++;

				deque<pair<int, int>> toGo;
				toGo.push_back({ i, j });
				while (!toGo.empty()) {
					pair<int, int> cur = toGo.front();
					toGo.pop_front();

					if (!check[cur.first][cur.second]) {
						check[cur.first][cur.second] = true;

						if (isInRange(cur.first - 1, cur.second, arg) && arg[cur.first - 1][cur.second]) {
							toGo.push_back({ cur.first - 1, cur.second });
						}
						if (isInRange(cur.first + 1, cur.second, arg) && arg[cur.first + 1][cur.second]) {
							toGo.push_back({ cur.first + 1, cur.second });
						}
						if (isInRange(cur.first, cur.second - 1, arg) && arg[cur.first][cur.second - 1]) {
							toGo.push_back({ cur.first, cur.second - 1 });
						}
						if (isInRange(cur.first, cur.second + 1, arg) && arg[cur.first][cur.second + 1]) {
							toGo.push_back({ cur.first, cur.second + 1 });
						}
					}
				}
			}
		}
	}

	return num;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int ITER = 0;
	cin >> ITER;
	while (ITER > 0) {
		int N = 0, M = 0, K = 0;
		cin >> M >> N >> K;
		vector<vector<bool>> ground(N, vector<bool>(M, false));
		for (int i = 0, temp[2]; i < K; i++) {
			cin >> temp[0] >> temp[1];
			ground[temp[1]][temp[0]] = true;
		}

		cout << getNumber(ground) << '\n';
		ITER--;
	}

	return 0;
}