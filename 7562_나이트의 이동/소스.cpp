#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef struct MOVE {
	pair<int, int> dir;
	int num;
}mv;

bool isInRange(const pair<int, int> dir, const int N) {
	if (0 <= dir.first && dir.first < N && 0 <= dir.second && dir.second < N) {
		return true;
	}
	return false;
}

int getNumber(const pair<int, int> &start, const pair<int, int> &dest, const int N) {
	int counter = 0;
	vector<vector<bool>> check(N, vector<bool>(N, false));
	queue<mv> togo;

	togo.push({ start, 0 });
	while (!togo.empty()) {
		pair<int, int> cur_dir = togo.front().dir;
		int cur_num = togo.front().num;
		togo.pop();

		if (cur_dir == dest) {
			counter = cur_num;
			break;
		}
		else if (!check[cur_dir.first][cur_dir.second]) {
			check[cur_dir.first][cur_dir.second] = true;

			if (isInRange({ cur_dir.first - 1, cur_dir.second - 2 }, N) && !check[cur_dir.first - 1][cur_dir.second - 2]) {
				togo.push({ {cur_dir.first - 1, cur_dir.second - 2},cur_num + 1 });
			}
			if (isInRange({ cur_dir.first - 2, cur_dir.second - 1 }, N) && !check[cur_dir.first - 2][cur_dir.second - 1]) {
				togo.push({ {cur_dir.first - 2, cur_dir.second - 1},cur_num + 1 });
			}
			if (isInRange({ cur_dir.first - 2, cur_dir.second + 1 }, N) && !check[cur_dir.first - 2][cur_dir.second + 1]) {
				togo.push({ {cur_dir.first - 2, cur_dir.second + 1},cur_num + 1 });
			}
			if (isInRange({ cur_dir.first - 1, cur_dir.second + 2 }, N) && !check[cur_dir.first - 1][cur_dir.second + 2]) {
				togo.push({ {cur_dir.first - 1, cur_dir.second + 2},cur_num + 1 });
			}
			if (isInRange({ cur_dir.first + 1, cur_dir.second + 2 }, N) && !check[cur_dir.first + 1][cur_dir.second + 2]) {
				togo.push({ {cur_dir.first + 1, cur_dir.second + 2},cur_num + 1 });
			}
			if (isInRange({ cur_dir.first + 2, cur_dir.second + 1 }, N) && !check[cur_dir.first + 2][cur_dir.second + 1]) {
				togo.push({ {cur_dir.first + 2, cur_dir.second + 1},cur_num + 1 });
			}
			if (isInRange({ cur_dir.first + 2, cur_dir.second - 1 }, N) && !check[cur_dir.first + 2][cur_dir.second - 1]) {
				togo.push({ {cur_dir.first + 2, cur_dir.second - 1},cur_num + 1 });
			}
			if (isInRange({ cur_dir.first + 1, cur_dir.second - 2 }, N) && !check[cur_dir.first + 1][cur_dir.second - 2]) {
				togo.push({ {cur_dir.first + 1, cur_dir.second - 2},cur_num + 1 });
			}
		}
	}

	return counter;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	int iter = 0;
	cin >> iter;

	for (int t = 0; t < iter; t++) {
		int N = 0;
		pair<int, int> start, dest;
		cin >> N >> start.first >> start.second >> dest.first >> dest.second;

		cout << getNumber(start, dest, N) << '\n';
	}

	return 0;
}