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
	q.push({ { {0, 0} , 1 }, 1}); // y, x, block ������ �ִ� Ƚ��
	visited[0][0][0] = true;

	while (!q.empty()) {
		int row = q.front().first.first.first;
		int col = q.front().first.first.second;
		int block = q.front().first.second;
		int count = q.front().second;
		q.pop();

		// �������� �������� ��,
		if (row == graph.size() - 1 && col == graph.front().size() - 1) {
			return count;
		}

		for (uint32_t i = 0; i < moveDir.size(); i++) {
			int newrow = row + moveDir[i].y;
			int newcol = col + moveDir[i].x;

			// ���� ����� �ʰ�,
			if (isInRange(newrow, newcol, graph)) {
				// �� ������ ��(��)�̰�, ���� ���� �ȶվ�����
				if (graph[newrow][newcol] == '1' && block != 0) {
					visited[newrow][newcol][block - 1] = true;
					q.push({ { { newrow, newcol }, block - 1 }, count + 1 });
				}
				// �� ���ִ� ���̰�, �湮���� �ʾҴٸ�
				if (graph[newrow][newcol] == '0' && !visited[newrow][newcol][block]) {
					visited[newrow][newcol][block] = true;
					q.push({ { { newrow, newcol }, block }, count + 1 });
				}
			}
		}
	}
	// �������� �������� ���ϰ� Ž���� ����Ǿ�����
	return -1;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, M = 0;

	/* ���� ũ�� �� �� ���� �Է� */
	cin >> N >> M;
	vector<string> graph(N);
	for (string &s: graph) {
		cin >> s;
	}

	/* bfs Ž�� ���� �� ��� ��� */
	cout << bfs(graph);

	return 0;
}
