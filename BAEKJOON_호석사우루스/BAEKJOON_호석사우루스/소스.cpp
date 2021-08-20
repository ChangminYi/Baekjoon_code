#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;
class node {
public:
	pint dir = make_pair(0, 0);
	int idx = 0;
	int dist = 0;
	node() {}
	node(pint _dir, int _idx, int _dist) :dir(_dir), idx(_idx), dist(_dist) {}
};

vector<pint> poss_dir = {
	make_pair(-1, 0),
	make_pair(0, 1),
	make_pair(1, 0),
	make_pair(0, -1)
};
vector<vector<int>> poss_dir_idx = {
	{0, 1, 2, 3},
	{0, 2},
	{1, 3}
};
const int WALL = -1;
const int INF = INT32_MAX / 2;

int n, m;
int min_dist;
pint stt_dir, end_dir;
vector<vector<int>> impulse;
vector<vector<vector<int>>> dist;
priority_queue<node, vector<node>, greater<node>> pq;

const bool operator>(const node& a, const node& b) {
	return a.dist > b.dist;
}

istream& operator>>(istream& in, pint& p) {
	return in >> p.first >> p.second;
}

pint operator+(const pint& a, const pint& b) {
	return make_pair(a.first + b.first, a.second + b.second);
}

bool in_range(const pint& p) {
	if (1 <= p.first && p.first <= n) {
		if (1 <= p.second && p.second <= m) {
			if (impulse[p.first][p.second] != WALL) {
				return true;
			}
		}
	}
	return false;
}

void dijk() {
	dist[stt_dir.first][stt_dir.second][0] = 0;
	pq.push(node(stt_dir, 0, 0));

	while (!pq.empty()) {
		node cur = pq.top();
		pq.pop();

		if (cur.dist <= dist[cur.dir.first][cur.dir.second][cur.idx]) {
			int nxt_idx = (cur.idx + 1) % 3;

			for (const int& d_idx : poss_dir_idx[nxt_idx]) {
				pint nxt = cur.dir + poss_dir[d_idx];

				if (in_range(nxt)) {
					int new_dist = cur.dist + impulse[nxt.first][nxt.second];
					int old_dist = dist[nxt.first][nxt.second][nxt_idx];

					if (new_dist < old_dist) {
						dist[nxt.first][nxt.second][nxt_idx] = new_dist;
						pq.push(node(nxt, nxt_idx, new_dist));
					}
				}
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m >> stt_dir >> end_dir;
	impulse = vector<vector<int>>(n + 1, vector<int>(m + 1));
	dist = vector<vector<vector<int>>>(n + 1, vector<vector<int>>(m + 1, vector<int>(3, INF)));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> impulse[i][j];
		}
	}

	dijk();
	min_dist = min({
		dist[end_dir.first][end_dir.second][0],
		dist[end_dir.first][end_dir.second][1],
		dist[end_dir.first][end_dir.second][2]
		});
	cout << (min_dist != INF ? min_dist : -1);

	return 0;
}