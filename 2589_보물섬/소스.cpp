#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

vector<pair<int, int>> moveSet = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

bool inRange(const pair<int, int> &a, const pair<int, int> &range) {
	if (0 <= a.first && a.first < range.first) {
		if (0 <= a.second && a.second < range.second) {
			return true;
		}
	}
	return false;
}


int bfs(const vector<string> &map, const pair<int, int> &start) {
	pair<int, int> boundary = make_pair(map.size(), map.front().size());
	vector<vector<int>> visit(map.size(), vector<int>(map.front().size(), 0));
	queue<pair<int, int>> togo;
	int dist = 0;

	visit[start.first][start.second] = 1;
	togo.push(start);
	while (!togo.empty()) {
		pair<int, int> current = togo.front();
		togo.pop();
		dist = max(visit[current.first][current.second], dist);

		for (uint32_t i = 0; i < moveSet.size(); i++) {
			pair<int, int> temp = make_pair(current.first + moveSet[i].first, current.second + moveSet[i].second);
			if (inRange(temp, boundary) && map[temp.first][temp.second] == 'L' && visit[temp.first][temp.second] == 0) {
				visit[temp.first][temp.second] = visit[current.first][current.second] + 1;
				togo.push(temp);
			}
		}
	}

	return dist - 1;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);


	int W = 0, H = 0;
	cin >> H >> W;
	vector<string> map(H);
	for (string &s : map) {
		cin >> s;
	}

	int maxLength = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (map[i][j] == 'L') {
				maxLength = max(maxLength, bfs(map, make_pair(i, j)));
			}
		}
	}

	cout << maxLength;

	return 0;
}