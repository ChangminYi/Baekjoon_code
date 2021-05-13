#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

#define MAX 1000

typedef struct {
	int y, x;
}dir;

vector<dir> moveDir = {
	{1, 0}, {0, 1}, {-1, 0}, {0, -1}
};


bool isInRange(int row, int col, vector<string> &graph) {
	return ( 0 <= row && row < graph.size() && 0 <= col && col < graph.front().size());
}

int bfs(vector<string> &graph) {
	vector<vector<vector<bool>>> visited(graph.size(), vector<vector<bool>>(graph.front().size(), vector<bool>(2, false)));
	queue<pair<pair<pair<int, int>, int>, int>> q;
	q.push({ { {0, 0} , 1 }, 1}); // y, x, block 뚫을수 있는 횟수
	visited[0][0][0] = true;

	while (!q.empty()) {
		int row = q.front().first.first.first;
		int col = q.front().first.first.second;
		int block = q.front().first.second;
		int count = q.front().second;
		q.pop();

		// 목적지에 도착했을 때,
		if (row == graph.size() - 1 && col == graph.front().size() - 1) {
			return count;
		}

		for (uint32_t i = 0; i < moveDir.size(); i++) {
			int newrow = row + moveDir[i].y;
			int newcol = col + moveDir[i].x;

			// 맵을 벗어나지 않고,
			if (isInRange(newrow, newcol, graph)) {
				// 갈 수없는 길(벽)이고, 벽을 아직 안뚫었을때
				if (graph[newrow][newcol] == '1' && block != 0) {
					visited[newrow][newcol][block - 1] = true;
					q.push({ { { newrow, newcol }, block - 1 }, count + 1 });
				}
				// 갈 수있는 길이고, 방문하지 않았다면
				if (graph[newrow][newcol] == '0' && !visited[newrow][newcol][block]) {
					visited[newrow][newcol][block] = true;
					q.push({ { { newrow, newcol }, block }, count + 1 });
				}
			}
		}
	}
	// 목적지에 도착하지 못하고 탐색이 종료되었을때
	return -1;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, M = 0;

	/* 맵의 크기 및 맵 정보 입력 */
	cin >> N >> M;
	vector<string> graph(N);
	for (string &s: graph) {
		cin >> s;
	}

	/* bfs 탐색 진행 및 결과 출력 */
	cout << bfs(graph);

	return 0;
}
