#include<iostream>
#include<cstring>
#include<queue>

#define MAX 100
using namespace std;

vector<pair<int, int>> dir = {
	{0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

void BFS(int a, int b, vector<vector<char>> &map, vector<vector<bool>> &visit) {
	queue<pair<int, int>> Q;
	Q.push(make_pair(a, b));
	visit[a][b] = true;

	while (!Q.empty()) {
		int x = Q.front().first;
		int y = Q.front().second;
		Q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dir[i].first;
			int ny = y + dir[i].second;

			if (nx >= 0 && ny >= 0 && nx < map.size() && ny < map.front().size()) {
				if (visit[nx][ny] == false) {
					if (map[nx][ny] == map[x][y]) {
						visit[nx][ny] = true;
						Q.push(make_pair(nx, ny));
					}
				}
			}
		}
	}
}



int main(void) {
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);

	int N = 0;
	cin >> N;

	vector<vector<char>> map(N, vector<char>(N));
	vector<vector<bool>> visit(N, vector<bool>(N, false));
	for (vector<char> &i : map) {
		for (char &j : i) {
			cin >> j;
		}
	}

	int Answer1 = 0, Answer2 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visit[i][j]) {
				BFS(i, j, map, visit);
				Answer1++;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visit[i][j] = false;
			if (map[i][j] == 'G') {
				map[i][j] = 'R';
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visit[i][j]) {
				BFS(i, j, map, visit);
				Answer2++;
			}
		}
	}

	cout << Answer1 << ' ' << Answer2 << '\n';

	return 0;
}