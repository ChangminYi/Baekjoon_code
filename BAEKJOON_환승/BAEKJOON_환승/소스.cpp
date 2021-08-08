#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_SIZE = 100001;
const int NOT_VISIT = -1;

int n, m, k;
vector<vector<int>> graph;
vector<int> dist;
queue<int> que;

int bfs(int start) {
	dist[start] = 1;
	que.push(start);

	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		if (cur == n) {
			return dist[n];
		}
		else {
			for (int& nxt : graph[cur]) {
				if (dist[nxt] == NOT_VISIT) {
					dist[nxt] = (nxt <= n ? dist[cur] + 1 : dist[cur]);
					que.push(nxt);
				}
			}
		}
	}

	return -1;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> k >> m;

	/*
	* ȯ���� ǥ���ϴ� m���� ���� ��� �߰�
	* ȯ���� �ݵ�� ���� ��带 ���ļ� ����
	* ���� ���� ������ Ƚ���� ���� ����
	*/
	graph = vector<vector<int>>(n + m + 1);
	dist = vector<int>(n + m + 1, NOT_VISIT);
	
	for (int i = 1, tmp; i <= m; i++) {
		for (int j = 0; j < k; j++) {
			cin >> tmp;
			graph[tmp].push_back(i + n);
			graph[i + n].push_back(tmp);
		}
	}

	cout << bfs(1);

	return 0;
}