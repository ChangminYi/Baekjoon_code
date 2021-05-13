#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lint;

int graph[1000005][2] = { 0 };

int main(void) {
	cin.sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	lint K;

	vector<int> stones;
	vector<bool> visited;
	vector<vector<int>> component;

	cin >> N >> M >> K;

	if (M <= 1) {
		cout << "YES\n";
		return 0;
	}

	stones.assign(N, 0);
	visited.assign(N, false);

	for (int i = 0; i < N; i++) {
		cin >> stones[i];
	}

	for (int i = 0, x = 0, y = 0; i < M; i++) {
		cin >> x >> y;
		x--; y--;

		if (x > y) {
			swap(x, y);
		}

		if (x == 0 && y == N - 1) {
			graph[x][0] = 1;
			graph[y][1] = 1;
		}
		else {
			graph[x][1] = 1;
			graph[y][0] = 1;
		}
	}

	for (int i = 0; i < N; i++) {
		if (visited[i]) {
			continue;
		}

		vector<int> comp;
		visited[i] = true;
		comp.push_back(i);

		int nxt = 1;
		while (!visited[(i + nxt) % N] && !graph[(i + nxt) % N][0]) {
			comp.push_back((i + nxt) % N);
			visited[(i + nxt) % N] = true;
			nxt += 1;
		}

		nxt = -1;
		while (!visited[(i + nxt + N) % N] && !graph[(i + nxt + N) % N][1]) {
			comp.push_back((i + nxt + N) % N);
			visited[(i + nxt + N) % N] = true;
			nxt -= 1;
		}

		component.push_back(comp);
	}

	lint total = 0;
	for (vector<int> &comp : component) {
		int minv = 0x7FFFffff;
		for (int &idx : comp) {
			minv = min(stones[idx], minv);
		}

		total += minv;
	}

	if (total <= K) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}

	return 0;
}