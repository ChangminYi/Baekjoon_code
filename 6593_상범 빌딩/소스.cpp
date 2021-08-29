#include <iostream>
#include <vector>
#include <queue>

#define MAX 30

using namespace std;

typedef struct INDEX{
	int x, y, z;
}index;

bool operator==(const index &a, const index &b) {
	if (a.x == b.x && a.y == b.y && a.z == b.z) {
		return true;
	}
	return false;
}

char building[MAX][MAX][MAX];
bool visit[MAX][MAX][MAX];
vector<index> moveSet = {
	{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1} ,{0, 0, -1}
};
int L = 0, R = 0, C = 0;

bool inRange(const index &a, const index &range) {
	if (0 <= a.x && a.x < range.x) {
		if (0 <= a.y && a.y < range.y) {
			if (0 <= a.z && a.z < range.z) {
				return true;
			}
		}
	}
	return false;
}

int bfs(const index &start, const index &end, const index &boundary) {
	int result = -1;
	queue<pair<index, int>> togo;

	togo.push(make_pair(start, 0));
	while (!togo.empty()) {
		index cur = togo.front().first;
		int cur_dist = togo.front().second;
		visit[cur.x][cur.y][cur.z] = true;
		togo.pop();

		if (cur == end) {
			result = cur_dist;
			break;
		}

		index temp;
		for (uint32_t i = 0; i < moveSet.size(); i++) {
			temp = { cur.x + moveSet[i].x, cur.y + moveSet[i].y, cur.z + moveSet[i].z };

			if (inRange(temp, boundary) && building[temp.x][temp.y][temp.z] == '.' && !visit[temp.x][temp.y][temp.z]) {
				togo.push(make_pair(temp, cur_dist + 1));
			}
		}
	}

	return result;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	while (true) {
		cin >> L >> R >> C;
		if (L == 0 && R == 0 && C == 0) {
			break;
		}

		index boundary = { L, R, C };
		index start, end;
		for (int i = 0; i < L; i++) {
			for (int j = 0; j < R; j++) {
				for (int k = 0; k < C; k++) {
					cin >> building[i][j][k];
					visit[i][j][k] = false;

					if (building[i][j][k] == 'S') {
						start = { i, j, k };
					}
					else if (building[i][j][k] == 'E') {
						end = { i, j, k };
						building[i][j][k] = '.';
					}
				}
			}
		}

		int distance = bfs(start, end, boundary);
		if (distance == -1) {
			cout << "Trapped!\n";
		}
		else {
			cout << "Escaped in " << distance << " minute(s).\n";
		}
	}

	return 0;
}