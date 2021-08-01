#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include <limits>
using namespace std;

typedef pair<int, int> pint;
typedef pair<int, pint> node;

const int INF = INT32_MAX / 2;
const vector<pint> dir = {
	make_pair(0, -1),
	make_pair(-1, 0),
	make_pair(0, 1),
	make_pair(1, 0)
};

int n, m, T, D;
vector<vector<int>> board;
priority_queue<node, vector<node>, greater<node>> pq;

int convert_height(char c) {
	return (isupper(c) ? c - 'A' : c - 'a' + 26);
}

pint operator+(const pint& a, const pint& b) {
	return make_pair(a.first + b.first, a.second + b.second);
}

bool reachable_height(const pint& cur, const pint& nxt) {
	return (abs(board[cur.first][cur.second] - board[nxt.first][nxt.second]) <= T);
}

bool in_range(const pint& p) {
	if (0 <= p.first && p.first < n) {
		if (0 <= p.second && p.second < m) {
			return true;
		}
	}
	return false;
}

int get_cost(int cur, int nxt) {
	if (cur < nxt) {
		return (nxt - cur) * (nxt - cur);
	}
	else {
		return 1;
	}
}

vector<vector<int>> dijkstra(pint start) {
	vector<vector<int>> dist(n, vector<int>(m, INF));

	dist[start.first][start.second] = 0;
	pq.push(make_pair(0, start));
	while (!pq.empty()) {
		int cur_dist = pq.top().first;
		pint cur = pq.top().second;
		pq.pop();

		if (cur_dist <= dist[cur.first][cur.second]) {
			for (const pint& d : dir) {
				pint nxt = cur + d;

				if (in_range(nxt) && reachable_height(cur, nxt)) {
					int new_val = cur_dist + get_cost(board[cur.first][cur.second], board[nxt.first][nxt.second]);
					int old_val = dist[nxt.first][nxt.second];

					if (new_val < old_val && new_val <= D) {
						dist[nxt.first][nxt.second] = new_val;
						pq.push(make_pair(new_val, nxt));
					}
				}
			}
		}
	}

	return dist;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m >> T >> D;
	board = vector<vector<int>>(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char tmp_char;
			cin >> tmp_char;
			board[i][j] = convert_height(tmp_char);
		}
	}

	vector<vector<int>> dist_up = dijkstra(make_pair(0, 0));
	int max_height = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int dist_down = dijkstra(make_pair(i, j))[0][0];

			if (dist_up[i][j] != INF && dist_down != INF && dist_up[i][j] + dist_down <= D) {
				max_height = max(max_height, board[i][j]);
			}
		}
	}

	cout << max_height;

	return 0;
}