#include<iostream>
#include <vector>
#include <algorithm>

#define MAX 20
using namespace std;

int R, C, answer;
char map[MAX][MAX];
bool visit[26];

vector<pair<int, int>> moveSet = {
	{0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

bool inRange(const pair<int, int> &now) {
	if (0 <= now.first && now.first < R) {
		if (0 <= now.second && now.second < C) {
			return true;
		}
	}
	return false;
}

void DFS(pair<int, int> start, int cnt) {
	answer = max(answer, cnt);

	for (uint32_t i = 0; i < moveSet.size(); i++) {
		pair<int, int> nxt = { start.first + moveSet[i].first, start.second + moveSet[i].second };

		if (inRange(nxt)) {
			if (visit[map[nxt.first][nxt.second] - 'A'] == false) {
				visit[map[nxt.first][nxt.second] - 'A'] = true;
				DFS(nxt, cnt + 1);
				visit[map[nxt.first][nxt.second] - 'A'] = false;
			}
		}
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
		}
	}

	visit[map[0][0] - 'A'] = true;
	DFS(make_pair(0, 0), 1);
	cout << answer;

	return 0;
}