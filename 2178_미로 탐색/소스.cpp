#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

int N, M;
bool visit[100][100];
pair<int, int> dir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int BFS() {
	queue<pair<pair<int, int>, int>> togo;
	togo.push({ {0, 0}, 1 });

	while (!togo.empty()) {
		pair<int, int> current = togo.front().first;
		int distance = togo.front().second;
		togo.pop();
		if (visit[current.first][current.second]) {
			continue;
		}

		visit[current.first][current.second] = true;
		for (int i = 0; i < 4; i++) {
			if (current.first + dir[i].first == N - 1 && current.second + dir[i].second == M - 1) {
				return distance + 1;
			}
			if (!visit[current.first + dir[i].first][current.second + dir[i].second]) {
				if ((current.first + dir[i].first >= 0 && current.second + dir[i].second >= 0) && (current.first + dir[i].first < N && current.second + dir[i].second < M)) {
					togo.push({ { current.first + dir[i].first, current.second + dir[i].second }, distance + 1 });
				}
			}
		}
	}
	return -1;
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		string temp;
		cin >> temp;
		for (int j = 0; j < M; j++) {
			if (temp[j] == '1') {
				visit[i][j] = false;
			}
			else {
				visit[i][j] = true;
			}
		}
	}

	cout << BFS();

	return 0;
}