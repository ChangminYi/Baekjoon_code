#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define MAX 125
#define INF 1000000000

using namespace std;

vector<pair<int, int>> moveSet = {
	{0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

int map[MAX][MAX];
int dist[MAX][MAX];
int N;

bool inRange(const pair<int, int> &p) {
	if (0 <= p.first && p.first < N) {
		if (0 <= p.second && p.second < N) {
			return true;
		}
	}
	return false;
}

int dijkstra() {
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

	pq.push(make_pair(map[0][0], make_pair(0, 0)));
	dist[0][0] = map[0][0];
	while (!pq.empty()) {
		pair<int, int> cur = pq.top().second;
		pq.pop();

		for (uint32_t i = 0; i < moveSet.size(); i++) {
			pair<int, int> temp = { cur.first + moveSet[i].first, cur.second + moveSet[i].second };
			if (inRange(temp)) {
				int newVal = dist[cur.first][cur.second] + map[temp.first][temp.second];
				int oldVal = dist[temp.first][temp.second];

				if (newVal < oldVal) {
					dist[temp.first][temp.second] = newVal;
					pq.push(make_pair(newVal, temp));
				}
			}
		}
	}

	return dist[N - 1][N - 1];
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int iter = 1;
	while (true) {
		cin >> N;
		if (N == 0) { break; }

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				dist[i][j] = INF;
			}
		}

		cout << "Problem " << iter++ << ": " <<dijkstra() << '\n';
	}

	return 0;
}